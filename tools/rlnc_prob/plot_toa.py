import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from shared import calc_lora_tpacket

sfs = [7, 8, 9, 10, 11, 12]
bws = [125E3, 250E3, 500E3]
fsizes = np.arange(10, 150, 10)
CR: int = 1

df = pd.DataFrame({
    'SF': [],
    'BW': [],
    'FSize': [],
    'Duration': []
})
df.set_index(['FSize'])

bw = 250E3
for sf in sfs:
    # for bw in bws:
    for fsize in fsizes:
        duration = calc_lora_tpacket(fsize, sf, bw, CR)

        row = [sf, bw, fsize, duration]
        length = len(df.index)
        df.loc[length] = row

    # plt.plot(fsizes, )
    

df.to_csv('6_lora_toa.csv')

fig, ax = plt.subplots()
for key, grp in df.groupby(['SF']):
    ax = grp.plot(ax=ax, kind='line', x='FSize', y='Duration',
                  marker='.', label=f"SF{key:.0f}")

plt.yscale("log")
plt.xlabel("Payload size [bytes]")
plt.ylabel("Time on Air [sec]")
plt.grid(True)
plt.legend()
plt.title("Packet ToA vs SF and payload size")
plt.savefig('6_lora_toa.pdf')

print(df)
