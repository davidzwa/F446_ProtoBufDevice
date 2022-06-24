from math import comb, ceil
from random import Random
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator, NullFormatter)

nullword = ['0xFF', '0xFF', '0xFF', '0xFF']
nullword_bytes = bytes([int(x, 0) for x in nullword])
rng = Random()


def signed8(value):
    return -(value & 0x80) | (value & 0x7f)


def equals_nullword(bytestring):
    return bytestring == nullword_bytes


def index_to_time(index, rate):
    return index / rate / 60 / 60


def parse_flash_file(path):
    file = open(path, "rb")

    # Skip standard headers
    header = file.read(4)
    reserved1 = file.read(4)
    reserved2 = file.read(4)
    reserved3 = file.read(4)

    sequence_numbers = []
    rssis = []
    snrs = []

    word = file.read(4)
    while word:
        if equals_nullword(word):
            print("Empty word found. Done.")
            break

        # Process word into measurement
        sequence_numbers.append(word[3] << 8 | word[2])
        rssis.append(word[1]-150)
        snrs.append(signed8(word[0]))

        # Iterate
        word = file.read(4)

    return sequence_numbers, rssis, snrs


def P(m, n, r, q):
    p = 1.0
    for i in range(0, n+r):
        p *= (1 - 1 / pow(q, m-i))
    return p


def pmf_binomial_prob(p_error, m, N):
    return comb(N, m) * pow(p_error, N - m) * pow(1-p_error, m)


def failure_rate(n, N, eps, q, include_rref, r=0):
    p_success = 0
    for m in range(n, N+1):
        rref_failure_prob = P(m, n, r, q)

        # Calculate PER failure probability
        per_failure_prob = pmf_binomial_prob(eps, m, N)

        # Include row-reduction failure probability
        if include_rref:
            p_success += per_failure_prob * rref_failure_prob
        else:
            p_success += per_failure_prob

    return 1 - p_success


def failure_rates(n, delta_max, PER, q, include_rref):
    redundancies = range(0, delta_max+1)

    failure_probs = []
    for delta in redundancies:
        failure_probs.append(failure_rate(n, n+delta, PER, 0, q, include_rref))

    return redundancies, failure_probs


def success_rates(n, delta_max, PER, q, include_rref):
    redundancies = range(0, delta_max+1)

    success_probs = []
    for delta in redundancies:
        success_probs.append(
            1.0 - failure_rate(n, n+delta, PER, q, include_rref))

    return redundancies, success_probs


def meanfilt(x, k):
    """Apply a length-k mean filter to a 1D array x.
    Boundaries are extended by repeating endpoints.

    https://stackoverflow.com/questions/61147532/mean-filter-in-python-without-loops
    """

    assert k % 2 == 1, "Mean filter length must be odd."
    assert x.ndim == 1, "Input must be one-dimensional."

    k2 = (k - 1) // 2
    y = np.zeros((len(x), k), dtype=x.dtype)
    y[:, k2] = x
    for i in range(k2):
        j = k2 - i
        y[j:, i] = x[:-j]
        y[:j, i] = x[0]
        y[:-j, -(i+1)] = x[j:]
        y[-j:, -(i+1)] = x[-1]
    return np.mean(y, axis=1)


def calculate_decoding_prob_devices(F, s_f, G, devices, q, PER, delta):
    # Total generation frame count
    f = ceil(F / (s_f))  # Frame count
    n_g = ceil(f / G)  # Generation count
    R = G * (1+delta)

    print(f"Firmware of {F} bytes")
    print(f"{f} frames")
    print(f"Number of gens {n_g}")
    print(f"{G}/{R} gen frame ratio")

    decoding_probs = []
    all_gen_probs = []
    all_devices_probs = []
    # part_devices_probs = []

    redundancies = range(0, R+1)
    for redundancy in redundancies:
        p_fail_decode = failure_rate(G, redundancy, PER, q, True)
        p_success_decode = 1.0 - p_fail_decode

        p_all_gen_success = pow(p_success_decode, n_g)

        # p_all_gen_failure = 1.0 - p_all_gen_success
        # Suspicious calculation
        # p_98perc_failure_prob = 0
        # min_devices = int(ceil(devices * device_perc))
        # for m in range(min_devices, devices+1):
        #     p_98perc_failure_prob += pmf_binomial_prob(
        #         p_all_gen_failure, m, devices)

        p_all_devices_success = pow(p_all_gen_success, devices)

        decoding_probs.append(p_success_decode)
        all_gen_probs.append(p_all_gen_success)
        all_devices_probs.append(p_all_devices_success)
        # part_devices_probs.append(p_98perc_failure_prob)

    # Old suspicious and heavy binomial calculation
    # device_perc = 0.99
    # plt.plot(redundancies, part_devices_probs, '--',
    #          label='98% Devices Prob', alpha=alpha)

    return redundancies, decoding_probs, all_gen_probs, all_devices_probs


def find_erasures(sequence_numbers, rate, print_debug=False):
    counter = 0
    last_seq_number = None
    packets_missed = 0
    resets = 0
    erasures_found = []
    timestrings = []
    for index in range(0, len(sequence_numbers)):
        sequence_number = sequence_numbers[index]

        # Startup
        if last_seq_number is None:
            last_seq_number = sequence_number

        seq_diff = sequence_number - last_seq_number
        if sequence_number == 0:
            last_seq_number = 0
            resets += 1
            counter = 0
            print("Diff 0 (start?)")

        if seq_diff > 1:
            missed_pkts = seq_diff - 1
            packets_missed += missed_pkts

            miss_entries = [1] * seq_diff
            miss_entries[-1] = 0
            erasures_found += miss_entries

            if print_debug:
                print("Packet count missing", missed_pkts, miss_entries)
        else:
            erasures_found.append(0)

        data_time = index_to_time(sequence_number, rate)
        timestrings.append(data_time)

        # Iterate
        last_seq_number = sequence_number
        counter += 1

    return timestrings, erasures_found, counter, last_seq_number, packets_missed, resets


def plot_erasures_PER(alpha, marker_size, sequence_numbers, rssis, snrs, title, rate, PER_filter):
    timestrings, erasures, counter, last_seq_number, packets_missed, resets = find_erasures(
        sequence_numbers, rate)

    print("First seq", sequence_numbers[0])
    print("Last seq", sequence_numbers[-1])
    print(len(erasures), "erasure/reception entries")
    print(f"{counter} measurements found, total packets missed {packets_missed}, resets {resets}")

    PER_output = meanfilt(np.array(erasures), PER_filter)
    
    # Reproduce vectors
    erasure_indices_time = np.arange(0, len(PER_output), 1) / (rate * 60)
    sequence_numbers_time = sequence_numbers / (rate * 60)
    
    # Extra debugging
    # print("PER mean length", len(erasure_indices),
    #       len(PER_output), timestrings[-1], step)

    fig, ax1 = plt.subplots()
    lns1 = ax1.scatter(erasure_indices_time, PER_output, s=1,
                       color='orange', label='PER estimate ($\epsilon$)')
    ax1.set_ylim([0, 1])
    ax1.set_ylabel("PER estimate ($\epsilon$)")
    
    ax2 = ax1.twinx()
    lns2 = ax2.scatter(sequence_numbers_time, sequence_numbers,
                     s=0.25,
                     label='Sequence Numbers')
    ax2.set_ylabel('Sequence Numbers')
    
    lns = [lns1, lns2]
    labs = [l.get_label() for l in lns]
    ax1.legend(lns, labs, loc=0)

    ax1.xaxis.set_major_locator(MultipleLocator(1))
    ax1.xaxis.set_minor_locator(MultipleLocator(0.5))
    ax1.xaxis.set_minor_formatter(NullFormatter())

    ax1.set_xlabel('Time (min)')
    plt.title(title)
    # l1 = ax1.scatter(timestrings, rssis,
    #                  color='orange',
    #                  alpha=alpha,
    #                  s=marker_size,
    #                  label='RSSI')
    # ax1.text(1, -95, "RSSI")
    # l2 = ax2.scatter(timestrings, snrs,
    #                  alpha=alpha,
    #                  s=marker_size,
    #                  label='SNR')
    # ax2.text(2, -7, "SNR")
    # # ax1.legend(handles=l1+l2)
    # ax1.set_xlabel('Time (h)')
    # ax1.set_title(title)
    # ax1.set_ylabel("RSSI [dBm]")
    # ax2.set_ylabel("SNR [dB]")

    return PER_output


def decide_simple(p):
    global rng
    return 1 if rng.random() <= p else 0


def calculate_burst_timeseries(count, p, r, burst_prr, good_prr, PER_decider):
    # 0 = B, 1 = G
    prev_state = 1
    new_state = 1  # Always mark as good without history for consistency
    samples = []

    steps = range(0, count+1)
    burst_durations = []
    burst_end_steps = []
    burst_start_steps = [0] if new_state == 0 else []
    good_per = 1 - good_prr
    burst_per = 1 - burst_prr

    for index in steps:
        error = None
        if new_state == 0:
            # Burst state
            error = PER_decider(burst_per)
            if prev_state != 0:
                burst_start_steps.append(index)

            # decide to stay
            new_state = not decide_simple(1-r)
            prev_state = 0

        elif new_state == 1:
            # Good state
            error = PER_decider(good_per)

            if prev_state != 1:
                duration = index - burst_start_steps[-1]
                if duration < 0:
                    raise Exception("Burst duration cannot be negative")
                burst_end_steps.append(index)
                burst_durations.append(duration)

            # decide to stay
            new_state = decide_simple(1-p)
            prev_state = 1

        else:
            raise Exception("Illegal markov state")

        if error is None:
            raise Exception("Error was not properly sampled")

        samples.append(error)

    # If last state was burst, we need to wrap that end/avg up
    if len(burst_start_steps) != len(burst_end_steps):
        duration = index - burst_start_steps[-1]
        if duration < 0:
            raise Exception("Burst duration cannot be negative")
        burst_end_steps.append(index)
        burst_durations.append(duration)

    return steps, samples, burst_start_steps, burst_end_steps, burst_durations


def calc_lora_toa(frame_size: int, SF: int, BW: int, CR: int, num_preamble: int = 8, impl_hdr: bool = False):
    """https://github.com/tanupoo/lorawan_toa"""
    tSymb = pow(2, SF) / BW
    tPreamble = (num_preamble + 4.25) * tSymb

    numerator = 8 * frame_size - 4 * SF + 28 + 16 - 20 * impl_hdr
    denominator = 4 * SF # Skipped low DR (=12) for now
    payload_symb = ceil(numerator / denominator) * (CR + 4)
    payload_symb_nb = 8 + max(payload_symb, 0)

    t_payload = payload_symb_nb * tSymb
    t_packet = tPreamble + t_payload
    return t_packet, t_payload, payload_symb, payload_symb_nb


def calc_lora_tpacket(frame_size: int, SF: int, BW: int, CR:int, num_preamble: int = 8, impl_hdr: bool = False):
    val, _, _, _ = calc_lora_toa(frame_size, SF, BW, num_preamble, CR, impl_hdr)
    return val
