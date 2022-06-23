import csv
from math import ceil
import numpy as np
import matplotlib.pyplot as plt
from shared import failure_rate
import matplotlib.ticker as mtick
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator, NullFormatter)
success_points = []
with open('20_gen_0_2PER.csv', newline='\n') as csvfile:
    reader = csv.DictReader(csvfile)

    for row in reader:
        success_points.append(int(row['RedundancyUsed']))

PER = 0.2
delta_max = 30
G = 20
redundancies = np.arange(0, delta_max+1, 1)
success_rates_0_256 = []
success_rates_0_256_perfect = []
q = pow(2, 8)
for delta in redundancies:
    total_sent = G + delta
    imperfect = failure_rate(G, total_sent, PER, pow(2, 8), False, 0)
    success_rates_0_256.append(1 - imperfect)

    # perfect = failure_rate(
    # 	G, total_sent, PER, pow(2, 8), True, 0)
    # success_rates_0_256_perfect.append(1 - perfect)

fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(mtick.PercentFormatter())

# Make a plot with major ticks that are multiples of 20 and minor ticks that
# are multiples of 5.  Label major ticks with '%d' formatting but don't label
# minor ticks.
ax.xaxis.set_major_locator(MultipleLocator(20))
# ax.xaxis.set_major_formatter(FormatStrFormatter('%d'))
# For the minor ticks, use no labels; default NullFormatter.
ax.xaxis.set_minor_locator(MultipleLocator(5))
ax.xaxis.set_minor_formatter(NullFormatter())

print(np.arange(0.5, max(redundancies) + 0.5, 1))
hist, bins = np.histogram(success_points,
                          bins=np.arange(0.5, max(redundancies) + 0.5, 1)) # Align the bin centers properly

# Convert x-axis to percentage
redundancies = 100*redundancies / G
bins = 100*bins / G

# Determine generation success threshold
model_success_threshold = 100*ceil(max(success_rates_0_256)) / G
measured_success_threshold = 100*ceil(max(success_points)) / G
max_threshold = 100*delta_max / G

cum_hist = np.cumsum(hist)
print(bins, len(bins), len(hist))
plt.bar(bins[:-1], hist/max(hist), alpha=0.4,
        color='orange', width=3.5, label='Measured success histogram')
plt.plot(bins[:-1], cum_hist/max(cum_hist),
         color='red', label='Decoder measured')
plt.plot(redundancies, success_rates_0_256, '--',
         color='black', label='Decoder model')
plt.axvspan(measured_success_threshold,
            max_threshold, color='green', alpha=0.1)
plt.axvspan(0, measured_success_threshold, color='red', alpha=0.1)
plt.text(measured_success_threshold + (max_threshold - measured_success_threshold)
         * 0.1, 0.5, "Success", alpha=0.2, rotation=90, verticalalignment='center')
plt.text((measured_success_threshold)*0.8, 0.5, "Failure",
         alpha=0.2, rotation=90, verticalalignment='center')
plt.vlines(measured_success_threshold, 0, 1, color='green',
           linestyles='solid', label='Measured success threshold')
# plt.grid(True)

plt.legend()
plt.xlabel('Redundancy [%]')
plt.ylabel('Decoding Probability')
plt.title(f'Decoding probability vs redundancy ($\epsilon$=20%, G={G}, R=80)')
plt.savefig('20_rlnc_result_per20.pdf')

print(len(redundancies))
print(f"redundancies: {redundancies}")

print(f"measured_success_threshold: {measured_success_threshold:.0f} %")
