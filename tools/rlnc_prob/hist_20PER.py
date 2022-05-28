import csv
import numpy as np
import matplotlib.pyplot as plt
from shared import failure_rate
import matplotlib.ticker as mtick

max_red = 60
vals = []
with open('20_gen_0_2PER.csv', newline='\n') as csvfile:
	reader = csv.DictReader(csvfile)

	for row in reader:
		vals.append(int(row['RedundancyUsed']))

PER = 0.2
delta_max = 60
threshold = 20
redundancies = np.arange(0, delta_max+1, 1)
success_rates_0_256 = []
success_rates_0_256_perfect = []
q = pow(2, 8)
for delta in redundancies:
    total_sent = threshold + delta
    imperfect = failure_rate(threshold, total_sent, PER, pow(2, 8), False, 0)
    perfect = failure_rate(
    	threshold, total_sent, PER, pow(2, 8), True, 0)
    success_rates_0_256.append(1 - imperfect)
    success_rates_0_256_perfect.append(1 - perfect)

fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(mtick.PercentFormatter())

hist, bins = np.histogram(vals, bins=max_red, range=[0, 60])

# Convert x-axis to percentage
redundancies = 100*redundancies / threshold
bins = 100*bins / threshold

cum_hist = np.cumsum(hist)
plt.bar(bins[:-1], hist/max(hist), alpha=0.4,
        color='green', width=3.5, label='RLNC histogram')
plt.plot(bins[:-1], cum_hist/max(cum_hist), color='orange', label='RLNC measured')
plt.plot(redundancies, success_rates_0_256, label='RLNC model')
plt.grid(True)
plt.legend()
plt.xlabel('Redundancy [%]')
plt.ylabel('Decoding Probability')
plt.title('Decoding success vs redundancy (PER 20%, n=20)')
plt.savefig('20_rlnc_result_per20.pdf')
