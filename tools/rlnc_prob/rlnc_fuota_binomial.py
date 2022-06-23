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
             label='Single Generation', alpha=alpha)
    plt.plot(redundancies, all_gens, '--',
             label='All Generations', alpha=alpha)
    plt.plot(redundancies, devices, '--',
             label='All Devices', alpha=alpha)

    # Calculate heuristic worst-case network success threshold
    success_threshold_pre = np.argwhere(np.array(devices) > 0.999)
    
    # Apply the success threshold if it is known, otherwise mark complete failure
    max_red = max(redundancies)
    min_red = min(redundancies)
    if len(success_threshold_pre) > 0:
        # Collect minimum success point
        success_threshold = success_threshold_pre[0]
        
        # Convert to redundancy percentage
        success_threshold_perc = 100*(success_threshold[0]-G) / G
        print(f"PER: {PER}, needed redundancy: {success_threshold_perc:.1f}%")
        plt.axvspan(success_threshold_perc, max_red, color='green', alpha=0.1)
        plt.axvspan(min_red, success_threshold_perc, color='red', alpha=0.1)
        plt.text(success_threshold_perc + (max_red - success_threshold_perc)
                 / 2, 0.5, "Success", alpha=0.2, rotation=90, verticalalignment='center')
        plt.vlines(success_threshold_perc, 0, 1, color='green',
                   linestyles='solid', label='99.9% success threshold')

        plt.text((min_red + success_threshold_perc)*0.5, 0.5, "Failure",
         alpha=0.2, rotation=90, verticalalignment='center')
    else:
        plt.axvspan(min_red, max_red,color='red', alpha=0.1)
        plt.text((max_red)*0.7, 0.5, "Failure",
                 alpha=0.2, rotation=90, verticalalignment='center')
    
    # plt.grid(True)
    plt.legend()
    
    plt.xlabel('Redundancy [%]')
    plt.ylabel('Decoding Probability')
    size = int(ceil(F/1E3))
    eps = PER*100
    label = '$U_{firmware}$'
    plt.title(
        f"Decoding Probability vs Redundancy ({label}={size}kB,G=20,R=80,$\epsilon$={eps:.0f}%)")

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
