p = 0.0015  # move to burst prob
r = 0.03  # move to good prob (stays stuck)
h = 1  # 100% PER
k = 0.03  # 5% PER
count = 10000
init = 1  # Good/Burst initial state

pi_G, pi_B, p_E = calculate_steady_state(p,r,h,k)
steps, samples = calculate_burst_timeseries(init, count, p, r, h, k)
_, samples2 = calculate_burst_timeseries(init, count, 0.001, r, h, k)

avg = np.average(samples)
err = abs(p_E - avg)
print(f"Err: {err:.3f} Sim: {avg:.3f} SS: {p_E:.3f}")

plt.plot(steps, meanfilt(np.array(samples), 91),
         label='Packet Reception', alpha=0.6)
plt.plot(steps, meanfilt(np.array(samples2), 91),
         label='Packet Reception better', alpha=0.6)