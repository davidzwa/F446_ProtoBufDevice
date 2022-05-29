import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from shared import success_rates
import pandas as pd

PER = 0.2
delta_max = 60
threshold = 20
N_G = 30
q = pow(2, 8)
csv_file = '21_experiment_filtered_gen_updates.csv'
df = pd.read_csv(csv_file)

colors = ['green']
color_index = 0
gk = df[df.Success == True].groupby('PerConfig')

# Set percentage
fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(mtick.PercentFormatter())

# Construct colormap
colors = plt.cm.viridis(np.linspace(0, 1, len(gk)-1))

output_data = []
df_model = pd.DataFrame({'Redundancy': [], 'SuccessRate': [], 'PER': []})
for per_name, group in gk:

    print("Plotting PER", per_name, type(per_name))
    if per_name == 0.0:
        continue

    grp = group['RedundancyUsed']

    # Get histogram from data and run through model
    hist, bins = np.histogram(grp, bins=delta_max, range=[0, 60])
    reds, y = success_rates(threshold, delta_max, per_name, q, False)

    # Append to series for csv export
    added_df = pd.DataFrame(
        {'Redundancy': list(reds), 'SuccessRate': y, 'PER': [per_name] * len(reds)})
    df_model = pd.concat([df_model, added_df], ignore_index=True)

    # Rescale x-axes
    reds = 100*np.array(reds)/threshold
    bins = 100*bins/threshold

    # Cumulative norm by gen count N_G
    plt.plot(bins[:-1], np.cumsum(hist)/N_G, color=colors[color_index])

    plt.plot(reds, y, '--', color='black')
    label = '{0}'.format(per_name)
    plt.text(color_index * 6 * 5, y[30] - color_index / 350, label)

    color_index += 1

df_model.to_csv('21_output.csv')

plt.grid(True)
plt.xlabel('Redundancy [%]')
plt.ylabel('Decoding Probability')
plt.title('Decoding success vs redundancy (PER [10%-80%], n=20)')
plt.savefig('21_rlnc_vs_model.pdf')

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
