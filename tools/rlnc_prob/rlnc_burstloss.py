from math import ceil, exp, factorial
import matplotlib.pyplot as plt
import pandas as pd
from random import Random
import numpy as np
from shared import meanfilt

rng = Random()
plot_count = 1


def decide(p):
    global rng
    return 1 if rng.random() <= p else 0


def calculate_steady_state(p, r, h, k):
    pi_G = r / (r+p)
    pi_B = p / (r+p)
    p_E = (1-k)*pi_G + (1-h)*pi_B

    return pi_G, pi_B, p_E


def calculate_burst_duration_pmf(count, r):
    steps = range(0, count + 1)
    pmf = []
    for k in steps:
        # val = pow(lam, k) * exp(-lam) / factorial(k)
        val = pow(1-r, k) * r
        pmf.append(val)

    return steps, pmf


def calculate_burst_timeseries(init, count, p, r, h, k):
    # 0 = B, 1 = G
    state = 1 if init else 0
    samples = []

    steps = range(0, count)
    burst_durations = []
    burst_end_steps = []
    burst_start_steps = [0] if state == 0 else []

    for index in steps:
        error = None
        if state == 0:
            # Burst state
            error = decide(h)

            # decide to stay
            state = not decide(1-r)

            if state == 1:
                duration = index - burst_start_steps[-1]
                if duration < 0:
                    raise Exception("Burst duration cannot be negative")
                burst_end_steps.append(index)
                burst_durations.append(duration)

        elif state == 1:
            # Good state
            error = decide(k)

            # decide to stay
            state = decide(1-p)

            if state == 0:
                burst_start_steps.append(index)
        else:
            raise Exception("Illegal markov state")

        if error is None:
            raise Exception("Error was not properly sampled")

        samples.append(error)

    return steps, samples, burst_start_steps, burst_end_steps, burst_durations

x = 0.25
p = 0.01  # move to burst prob
r = 0.05  # move to good prob (stays stuck)
r2 = 0.02
h = 0  # 100% PER
k = 1  # 0% PER
count = 1500000
init = 1  # Good/Burst initial state
filter_window = 1501
pmf_steps = ceil(3 * 1/r2)

# Calculate PMF
plt.figure(plot_count)
plot_count += 1
steps3, pmf = calculate_burst_duration_pmf(pmf_steps, r)
steps4, pmf2 = calculate_burst_duration_pmf(pmf_steps, r2)
plt.plot(steps3, pmf, label='Burst Duration PMF')
plt.plot(steps4, pmf2, label='Burst Duration PMF Bad')
# plt.grid(True)
# plt.legend()
# plt.xlabel('Packet count')
# plt.ylabel('Burst duration probability')
# plt.title(f"Burst duration PMF vs packet count")
# plt.show(block=False)

# Simulate Burst
pi_G, pi_B, p_E = calculate_steady_state(p, r, h, k)
steps, samples, bs, be, bdiff = calculate_burst_timeseries(
    init, count, p, r, h, k)
steps2, samples2, bs2, be2, bdiff2 = calculate_burst_timeseries(
    init, count, p, r2, h, k)

if (len(bdiff) > 0):
    max_burst = max(bdiff)
    avg_burst = np.average(bdiff)
    min_burst = min(bdiff)
    num_bursts = len(bdiff)
    print(
        f"1) Max: {max_burst}, Avg: {avg_burst: .2f}, Min: {min_burst}, Count: {num_bursts}")
if (len(bdiff2) > 0):
    max_burst = max(bdiff2)
    avg_burst = np.average(bdiff2)
    min_burst = min(bdiff2)
    num_bursts = len(bdiff)
    print(
        f"2) Max: {max_burst}, Avg: {avg_burst: .2f}, Min: {min_burst}, Count: {num_bursts}")

avg = np.average(samples)
err = abs(p_E - avg)
print(f"Err: {err:.3f} Sim: {avg:.3f} SS: {p_E:.3f}")

bin_count = 50
# plt.figure(plot_count)
# plot_count += 1
# hist, bins = np.histogram(bdiff, bins=bin_count, range=[0, pmf_steps+1], histtype='step')
# print(hist)
# hist2, bins2 = np.histogram(bdiff2, bins=bin_count,
#                             range=[0, pmf_steps+1], histtype='step')
# plt.bar(bins[:-1], hist, label='Bad burst duration')
plt.hist(bdiff, bins=bin_count, range=[
         0, pmf_steps+1], label='Bad burst duration', histtype='step', density=True)
# plt.bar(bins2[:-1], hist2, label='Good burst duration')
plt.hist(bdiff2, bins=bin_count, range=[
         0, pmf_steps+1], label='Good burst duration', histtype='step', density=True)
plt.xlabel("Burst duration (bins)")
plt.ylabel("Duration Probability")
plt.grid(True)
plt.legend()
plt.title("Duration histograms and PMFs")
# plt.show()
plt.savefig('25_burst_duration_pmf_histos.pdf')

# Export data and PDF plots
df_data = pd.DataFrame({'Start': bs, 'Duration': bdiff, 'End': be})
df_data.to_csv('26_burst_durations.csv')
df_data2 = pd.DataFrame({'Start': bs2, 'Duration': bdiff2, 'End': be2})
df_data2.to_csv('26_burst_durations_worse.csv')

# Show timeseries
plt.figure(plot_count)
plot_count += 1
filtered = meanfilt(np.array(samples), filter_window)
plt.plot(steps, filtered, label='Packet Reception', alpha=0.6)
filtered2 = meanfilt(np.array(samples2), filter_window)
plt.plot(steps2, filtered2, label='Packet Reception better', alpha=0.6)
plt.grid(True)
plt.legend()
plt.xlabel('Packet index')
plt.ylabel('Reception Probability')
plt.title(f"Successful Reception with burst - time series")
plt.show(block=False)

# Export data and PDF plots
plt.savefig('24_timeseries_burst.pdf')
# df_data = pd.DataFrame({'Steps': steps, 'Success': samples, 'Filtered': filtered})
# df_data2 = pd.DataFrame(
#     {'Steps': steps2, 'Success': samples2, 'Filtered': filtered2})
# df_data.to_csv('24_timeseries_burst.csv')
# df_data2.to_csv('24_timeseries_burst_worse.csv')
