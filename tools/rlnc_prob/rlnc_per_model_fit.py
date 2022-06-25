import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import matplotlib.ticker as mtick
from shared import success_rates
import pandas as pd

eps = 0.2 # PER
delta_max = 120 # R - G
G = 20
N_G = 30
q = pow(2, 8)

colors = ['green']
color_index = 0


# Set percentage
fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(mtick.PercentFormatter())

# Construct colormap
gk = np.arange(0.1, 0.9, 0.1)
# colors = plt.cm.viridis(np.linspace(0, 1, len(gk)-1))
colors = plt.cm.inferno(np.linspace(0.1, .8, len(gk)))

output_data = []
df_model = pd.DataFrame({'Redundancy': [], 'SuccessRate': [], 'PER': []})
for per_name in gk:
    print("Plotting PER", per_name, type(per_name))
    
    # Get histogram from data and run through model
    reds, model = success_rates(G, delta_max, per_name, q, False)
    
    model_diff = np.diff(model)
    mu, std = norm.fit(model_diff)
    print(f"Distribution fit mu:{mu} std:{std}")

    # plt.plot(reds, model, '--', color='black')
    per = per_name * 100
    plt.plot(reds[:-1], model_diff, label=f'PER {per:.0f}%', color=colors[color_index])

    color_index += 1

df_model.to_csv('21b_output.csv')

plt.legend(loc='center')
# plt.grid(True)
plt.xlabel('Redundancy [%]')
plt.ylabel('Decoding probability')
plt.title('Decoding PDF ($\epsilon$ [10%-80%], G=20)')
plt.savefig('21b_rlnc_model.pdf')
