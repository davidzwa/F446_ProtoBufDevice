from math import pow, ceil
import numpy as np

import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from shared import calculate_decoding_prob_devices

"""
We calculate the probability that a firmware update succeeds for a certain amount of devices.
"""

plot_count = 1


def save_device_plot(plot_prefix, F, s_f, G, devices, q, PER, delta):
    redundancies, decode, all_gens, devices = calculate_decoding_prob_devices(
        F, s_f, G, devices, q, PER,  delta)

    global plot_count
    
    plt.figure(plot_count)
    fig, ax = plt.subplots()
    ax.xaxis.set_major_formatter(mtick.PercentFormatter())
    
    plot_count += 1
    alpha = 1.0
    # Rescale the x-axis to percentages
    redundancies = 100*(np.array(redundancies)-G) / G
    plt.plot(redundancies, decode,
             label='Decoding Prob', alpha=alpha)
    plt.plot(redundancies, all_gens, '--',
             label='All Gen Prob', alpha=alpha)
    plt.plot(redundancies, devices, '--',
             label='100% Devices Prob', alpha=alpha)

    plt.grid(True)
    plt.legend()
    plt.xlabel('Redundancy [%]')
    plt.ylabel('Decoding Probability')
    size = int(ceil(F/1E3))
    plt.title(f"{size}kB vs Redundancy (n=20,N=80,PER={PER:.1f})")

    filename = f'{plot_prefix}_{PER:.1f}PER.pdf'
    print(f"Exporting pdf plot {filename}")
    plt.savefig(filename)


# First contextualize the firmware update
F = 6E3
G = 20  # Generation frame count
q = pow(2, 8)
s_f = 10  # symbols = bytes
N_d = 3000
# PER = 0.2
delta = 3  # 300% so in total 80 packets per generation

for PER in np.arange(0, 0.6, 0.1):
    plot_prefix = '23_alldevices_prob'
    save_device_plot(plot_prefix, F, s_f, G, N_d, q, PER, delta)

# PER = 0.3
# plot_prefix = '24_alldevices_prob'
# save_device_plot(plot_prefix, F, s_f, G, N_d, q, PER, delta)

exit(0)
