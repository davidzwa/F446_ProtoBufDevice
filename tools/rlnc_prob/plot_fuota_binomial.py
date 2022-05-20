from math import pow, ceil

import matplotlib.pyplot as plt
from shared import failure_rate, pmf_binomial_prob
# We calculate the probability that a firmware update succeeds

# First contextualize the firmware update
PER = 0.3
F = 600E3
G = 20  # Generation frame count
q = pow(2, 8)
delta = 3  # 300% so in total 80 packets per generation
s_f = 10  # symbols = bytes

f = F / (s_f)  # Frame count
n_g = f / G  # Generation count
N = (1+delta) * G

device_perc = 0.98
devices = 3000

print(f"Number of frames {f} gens {n_g}")
# Packet count

decoding_probs = []
all_gen_probs = []
perc98_devices_probs = []

redundancies = range(0, N+1)
for redundancy in redundancies:
    p_fail = failure_rate(G, redundancy, PER, q, True)
    p_success_decode = 1 - p_fail

    
    p_all_gen_success = pow(p_success_decode, n_g)

    p_all_gen_failure = 1 - p_all_gen_success

    p_90perc_failure_prob = 0
    min_devices = int(ceil(devices * device_perc))
    for m in range(min_devices, devices+1):
        p_90perc_failure_prob += pmf_binomial_prob(
            p_all_gen_failure, m, devices)

    p_all_devices_success = pow(p_all_gen_success, devices)

    # if (p_all_devices_success > 0.9):
    #     print(f"{redundancy} \tSingleFail:\t{p_fail:.2f} \n\tAllGen({n_g:.0f}):\t{p_all_gen_success:.2f} \n\tAllDevices({devices}):\t{p_all_devices_success:.2f} \n\t98%Devices+:\t{p_90perc_failure_prob:.3f}")
    #     break

    all_gen_probs.append(p_all_gen_success)
    perc98_devices_probs.append(p_90perc_failure_prob)
    decoding_probs.append(p_success_decode)

alpha = 0.6
plt.plot(redundancies, decoding_probs,
         '*',
         label='Decoding Prob', alpha=alpha)
plt.plot(redundancies, all_gen_probs, '--',
         label='All Gen Prob', alpha=alpha)
plt.plot(redundancies, perc98_devices_probs, '--',
         label='98% Devices Prob', alpha=alpha)

plt.grid(True)
plt.legend()
plt.xlabel('Redundant packet count')
plt.ylabel('Decoding Failure Probability')
plt.title("Completion 60kB FUOTA vs Redundancy (n=20, N=80, PER=0.2")
plt.show()

exit(0)
