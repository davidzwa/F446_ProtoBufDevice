from math import ceil
from statistics import mean
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from shared import meanfilt, calculate_burst_timeseries, decide_simple

plot_count = 1


def calculate_steady_state(p, r, h, k):
    pi_G = r / (r+p)
    pi_B = p / (r+p)
    p_E = (1-k)*pi_G + (1-h)*pi_B

    return pi_G, pi_B, p_E


def calculate_burst_duration_pmf(count, r):
    steps = range(0, count + 1)
    pmf = []
    for k in steps:
        # val = pow(lam, k) * exp(-lam) / factorial(k)
        val = pow(1-r, k) * r
        pmf.append(val)

    return steps, pmf


x = 0.25  # Short burst
x2 = 0.6  # Much longer burst
pi_b = 0.4  # 40% burst

p = x * pi_b  # move to burst prob
r = x * (1-pi_b)  # move to good prob (stays stuck)

# Worse
p2 = x2 * pi_b
r2 = x2 * (1-pi_b)

h = 0  # 100% PER
k = 1  # 0% PER
count = 5000000
filter_window = 1501
pmf_steps = ceil(10 * 1/r2)  # 150

# Calculate PMF
plt.figure(plot_count)
plot_count += 1
steps3, pmf = calculate_burst_duration_pmf(pmf_steps, r)
steps4, pmf2 = calculate_burst_duration_pmf(pmf_steps, r2)
plt.plot(steps4, pmf2, label='Burst Duration PMF (heavy, x=0.25)')
plt.plot(steps3, pmf, label='Burst Duration PMF (light, x=0.6)')

# Simulate Burst
pi_G, pi_B, p_E = calculate_steady_state(p, r, h, k)
pi_G2, pi_B2, p_E2 = calculate_steady_state(p2, r2, h, k)
steps, samples, bs, be, bdiff = calculate_burst_timeseries(
    count, p, r, h, k, decide_simple)
steps2, samples2, bs2, be2, bdiff2 = calculate_burst_timeseries(
    count, p2, r2, h, k, decide_simple)

if (len(bdiff) > 0):
    max_burst = max(bdiff)
    avg_burst = np.average(bdiff)
    min_burst = min(bdiff)
    num_bursts = len(bdiff)
    print(
        f"1) Max: {max_burst}, Avg: {avg_burst: .2f}, Min: {min_burst}, Count: {num_bursts}")
    avg = 1 - np.average(samples)
    err = abs(p_E - avg)
    print(f"1) Err: {err:.3f} Sim: {avg:.3f} SS: {p_E:.3f}")
if (len(bdiff2) > 0):
    max_burst = max(bdiff2)
    avg_burst = np.average(bdiff2)
    min_burst = min(bdiff2)
    num_bursts = len(bdiff)
    print(
        f"2) Max: {max_burst}, Avg: {avg_burst: .2f}, Min: {min_burst}, Count: {num_bursts}")
    avg2 = 1 - np.average(samples2)
    err2 = abs(p_E2 - avg)
    print(f"2) Err: {err2:.3f} Sim: {avg2:.3f} SS: {p_E2:.3f}")


bin_count = pmf_steps
plt.hist(bdiff, bins=bin_count, range=[
         0, pmf_steps+1], label='Burst histogram (heavy, x=0.25)', histtype='step', density=True)
plt.hist(bdiff2, bins=bin_count, range=[
         0, pmf_steps+1], label='Burst histogram (light, x=0.6)', histtype='step', density=True)
bin_size = round(pmf_steps / bin_count)
plt.xlabel(f"Burst Duration [Bin Size: {bin_size} time steps]")
plt.ylabel("Duration Probability")
plt.grid(True)
plt.legend()
plt.title("Duration histograms and PMFs")
plt.savefig('25_burst_duration_pmf_histos.pdf')

# Verify data length consistency
print(mean(bdiff), len(bs), len(bdiff), len(be))
print(mean(bdiff2), len(bs2), len(bdiff2), len(be2))

# Export data
df_data = pd.DataFrame({'Start': bs, 'Duration': bdiff, 'End': be})
df_data.to_csv('26_burst_durations.csv')
df_data2 = pd.DataFrame({'Start': bs2, 'Duration': bdiff2, 'End': be2})
df_data2.to_csv('26_burst_durations_worse.csv')

exit(0)

# Timeseries is not tractable/readable for 5 million messages
# Show timeseries
plt.figure(plot_count)
plot_count += 1
filtered = meanfilt(np.array(samples), filter_window)
plt.plot(steps, filtered, label='Packet Reception', alpha=0.6)
filtered2 = meanfilt(np.array(samples2), filter_window)
plt.plot(steps2, filtered2, label='Packet Reception better', alpha=0.6)
plt.grid(True)
plt.legend()
plt.xlabel('Packet index')
plt.ylabel('Reception Probability')
plt.title(f"Successful Reception with burst - time series")
# plt.show(block=False)

# Export data and PDF plots
plt.savefig('24_timeseries_burst.pdf')
# df_data = pd.DataFrame({'Steps': steps, 'Success': samples, 'Filtered': filtered})
# df_data2 = pd.DataFrame(
#     {'Steps': steps2, 'Success': samples2, 'Filtered': filtered2})
# df_data.to_csv('24_timeseries_burst.csv')
# df_data2.to_csv('24_timeseries_burst_worse.csv')
