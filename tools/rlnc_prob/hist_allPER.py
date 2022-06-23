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
    reds = 100*(np.array(reds))/threshold
    bins = 100*(bins)/threshold

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
plt.title('Decoding probability vs redundancy ($\epsilon$ [10%-80%], G=20)')
plt.savefig('21_rlnc_vs_model.pdf')
