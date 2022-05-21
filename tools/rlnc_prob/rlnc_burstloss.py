import matplotlib.pyplot as plt
import pandas as pd
from random import Random
import numpy as np
from shared import meanfilt

rng = Random()


def decide(p):
    global rng
    return 1 if rng.random() <= p else 0


def calculate_steady_state(p, r, h, k):
    pi_G = r / (r+p)
    pi_B = p / (r+p)
    p_E = (1-k)*pi_G + (1-h)*pi_B

    return pi_G, pi_B, p_E


def calculate_burst_timeseries(init, count, p, r, h, k):
    # 0 = B, 1 = G
    state = 1 if init else 0
    samples = []

    steps = range(0, count)
    for index in steps:
        error = None
        if state == 0:
            error = decide(1-h)

            # decide to stay
            state = not decide(1-r)
        elif state == 1:
            error = decide(1-k)

            # decide to stay
            state = decide(1-p)
        else:
            raise Exception("Illegal markov state")

        if error is None:
            raise Exception("Error was not properly sampled")

        samples.append(error)

    return steps, samples


p = 0.0015  # move to burst prob
p2 = 0.0005
r = 0.03  # move to good prob (stays stuck)
h = 1  # 100% PER
k = 0.03  # 3% PER
count = 10000
init = 1  # Good/Burst initial state
filter_window = 91

pi_G, pi_B, p_E = calculate_steady_state(p,r,h,k)
steps, samples = calculate_burst_timeseries(init, count, p, r, h, k)
steps2, samples2 = calculate_burst_timeseries(init, count, p2, r, h, k)

avg = np.average(samples)
err = abs(p_E - avg)
print(f"Err: {err:.3f} Sim: {avg:.3f} SS: {p_E:.3f}")

filtered = meanfilt(np.array(samples), filter_window)
plt.plot(steps, filtered, label='Packet Reception', alpha=0.6)
filtered2 = meanfilt(np.array(samples2), filter_window)
plt.plot(steps2, filtered2, label='Packet Reception better', alpha=0.6)
plt.grid(True)
plt.legend()
plt.xlabel('Packet index')
plt.ylabel('Reception Probability')
plt.title(f"Successful Reception with burst - time series")
plt.savefig('24_timeseries_burst.pdf')

df_data = pd.DataFrame({'Steps': steps, 'Success': samples, 'Filtered': filtered})
df_data2 = pd.DataFrame(
    {'Steps': steps2, 'Success': samples2, 'Filtered': filtered2})

df_data.to_csv('24_timeseries_burst.csv')
df_data2.to_csv('24_timeseries_burst_worse.csv')
