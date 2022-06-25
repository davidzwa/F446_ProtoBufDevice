import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import matplotlib.ticker as mtick
from shared import success_rates
import pandas as pd

eps = 0.2 # PER
delta_max = 60 # R - G
G = 20
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
    reds, model = success_rates(G, delta_max, per_name, q, False)
    
    mu, std = norm.fit(hist)
    print(mu, std)


    # Append to series for csv export
    added_df = pd.DataFrame(
        {'Redundancy': list(reds), 'SuccessRate': model, 'PER': [per_name] * len(reds)})
    df_model = pd.concat([df_model, added_df], ignore_index=True)

    # Rescale x-axes
    reds = 100*(np.array(reds))/G
    bins = 100*(bins)/G

    success_threshold_pre = np.argwhere(np.array(model) > 0.995)
    if len(success_threshold_pre) > 0:
        # Collect minimum success point
        success_threshold = success_threshold_pre[0]
        
        success_threshold_perc = 100*(success_threshold[0]) / G
        print("Threshold", success_threshold_perc)
        plt.vlines(success_threshold_perc, 1.025, 1.075, color=colors[color_index],
                   linestyles='solid', alpha=0.5)
        plt.text(success_threshold_perc, 1.08, f"$\epsilon$={per_name:.1f}")
        
        # Completed, Cumulative norm by gen count N_G
        plt.plot(bins[:-1], np.cumsum(hist)/N_G,
                 color=colors[color_index], label=f'Thr. {success_threshold_perc:.0f}%')
    
    else:
        # Failure, Cumulative norm by gen count N_G
        plt.plot(bins[:-1], np.cumsum(hist)/N_G,
             color=colors[color_index], label=f'$\epsilon$={per_name:.1f} (fail)')

    plt.plot(reds, model, '--', color='black')

    color_index += 1

df_model.to_csv('21_output.csv')

plt.legend(loc='center')
# plt.grid(True)
plt.xlabel('Redundancy [%]')
plt.ylabel('Decoding probability')
plt.title('Decoding probability vs redundancy ($\epsilon$ [10%-80%], G=20)')
plt.savefig('21_rlnc_vs_model.pdf')
