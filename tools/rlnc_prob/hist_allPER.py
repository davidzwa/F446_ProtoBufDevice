import numpy as np
import matplotlib.pyplot as plt
from shared import success_rates
import pandas as pd

PER = 0.2
delta_max = 60
threshold = 20
q = pow(2, 8)
csv_file = '21_experiment_filtered_gen_updates.csv'
df = pd.read_csv(csv_file)

colors = ['green']
color_index = 0
gk = df[df.Success == True].groupby('PerConfig')

output_data = []
df_model = pd.DataFrame({'Redundancy': [], 'SuccessRate': [], 'PER': []})
for name, group in gk:
    print("Plotting PER", name)

    grp = group['RedundancyUsed']

    hist, bins = np.histogram(grp, bins=delta_max, range=[0, 60])

    # plt.bar(bins[:-1], hist/max(hist), alpha=0.3, label='PER {0}%'.format(name*100.0))
    plt.plot(bins[:-1], np.cumsum(hist)/30, '--', alpha=0.8)

    label = '{0}'.format(name)
    x, y = success_rates(threshold, delta_max, name, q, False)

    added_df = pd.DataFrame(
        {'Redundancy': list(x), 'SuccessRate': y, 'PER': [name] * len(x)})

    df_model = pd.concat([df_model, added_df], ignore_index=True)

    plt.plot(x, y, alpha=0.8)
    plt.text(color_index * 5, y[30] - color_index / 350, label)

    color_index += 1

df_model.to_csv('output.csv')

plt.grid(True)
# plt.legend(bbox_to_anchor=(0.9, 0.95))
plt.xlabel('Redundant Packets sent')
plt.ylabel('Decoding Probability')
plt.title('Decoding success vs redundancy (PER [0%-80%], n=20)')
plt.show()


exit(0)


redundancies = range(0, delta_max+1)
failures_PERs = {}

for delta in redundancies:
    total_sent = threshold + delta
    imperfect = failure_rate(threshold, total_sent, PER, pow(2, 8), False, 0)
    perfect = failure_rate(threshold, total_sent, PER, pow(2, 8), True, 0)
    failure_rates_0_256.append(imperfect)
    failure_rates_0_256_perfect.append(perfect)
    print(imperfect - perfect)

hist, bins = np.histogram(vals, bins=max_red, range=[0, 60])
cum_hist = np.cumsum(hist)
plt.bar(bins[:-1], hist/max(hist), alpha=0.2,
        color='green', label='RLNC histogram')
plt.plot(bins[:-1], cum_hist/max(cum_hist), alpha=0.9,
         color='orange', label='RLNC measured')
plt.plot(redundancies, failure_rates_0_256, alpha=0.6, label='RLNC model')
# plt.plot(redundancies, failure_rates_0_256_perfect, '--', alpha=0.6)
# print(hist, bin_edges)
