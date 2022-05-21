from math import comb, ceil


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
            1 - failure_rate(n, n+delta, PER, 0, q, include_rref))

    return redundancies, success_probs


def calculate_decoding_prob_devices(F, s_f, G, devices, q, PER, delta):   
    # Total generation frame count
    f = ceil(F / (s_f))  # Frame count
    n_g = ceil(f / G)  # Generation count
    N = G * (1+delta)
    
    print(f"Firmware of {F} bytes")
    print(f"{f} frames")
    print(f"Number of gens {n_g}")
    print(f"{G}/{N} gen frame ratio")
    
    decoding_probs = []
    all_gen_probs = []
    all_devices_probs = []
    # part_devices_probs = []

    redundancies = range(0, N+1)
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
