import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from shared import success_rates
import pandas as pd

eps = 0.2  # PER
delta_max = 60  # R - G
G = 20
N_G = 30
q = pow(2, 8)
csv_file = '21_experiment_filtered_gen_updates.csv'
df = pd.read_csv(csv_file)

colors = ['green']
color_index = 0
per_groups = df[df.Success == True].groupby('PerConfig')

# Set percentage
fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(mtick.PercentFormatter())

# Construct colormap
colors = plt.cm.viridis(np.linspace(0, 1, len(per_groups)-1))

# Plotted data
output_data = []
pers = []

# Output dataframe
df_model = pd.DataFrame({'Redundancy': [], 'SuccessRate': [], 'PER': []})

# Iterate data
for per_name, group in per_groups:

    print("Plotting PER", per_name, type(per_name))
    if per_name == 0.0:
        continue

    
    grp_PER = group['MissedPackets'] / (group['MissedPackets'] + group['ReceivedPackets'])

    # Get histogram from data and run through model
    output_data.append(grp_PER * 100)
    pers.append(per_name * 100)

    # plt.plot(reds, model, '--', color='black')

    color_index += 1


df_model.to_csv('29_real_per_boxplot.csv')
plt.boxplot(output_data, positions=pers, widths=[2] * len(pers))
plt.plot(pers, np.array(pers), label='PER expected value [%]')
plt.legend()
# plt.grid(True)
plt.xlabel('Configured PER ($\epsilon$) [%]')
plt.ylabel('Estimated PER ($\epsilon$)')
plt.title('Estimated PER vs input PER ($\epsilon$ [10%-80%], G=20, R=80)')
plt.savefig('29_real_per_boxplot.pdf')
