from scipy.stats import binom
import matplotlib.pyplot as plt
from shared import failure_rate
import csv

paper_values = [0.99, 0.98, 0.97, 0.95, 0.87,
                0.77, 0.66, 0.54, 0.41, 0.295, 0.21]
PER = 0.2
alpha = 0.8
delta_max = 10
threshold = 16
redundancies = range(0, delta_max+1)
failure_rates_0_8 = []
failure_rates_0_4 = []
failure_rates_0_2 = []
failure_rates_0_1 = []
perfect_rates = []
output_data = []
employee_info = ['FieldSize', 'FailureRate']

for delta in redundancies:
    total_sent = threshold + delta
    perfect_rate = failure_rate(
        threshold, total_sent, PER, pow(2, 8), False, 0)
    rate_8 = failure_rate(threshold, total_sent, PER, pow(2, 8), True, 0)
    rate_4 = failure_rate(threshold, total_sent, PER, pow(2, 4), True, 0)
    rate_2 = failure_rate(threshold, total_sent, PER, pow(2, 2), True, 0)
    rate_1 = failure_rate(threshold, total_sent, PER, pow(2, 1), True, 0)

    output_data.append({'FieldSize': 8, 'FailureRate': rate_8})
    output_data.append({'FieldSize': 4, 'FailureRate': rate_4})
    output_data.append({'FieldSize': 2, 'FailureRate': rate_2})
    output_data.append({'FieldSize': 1, 'FailureRate': rate_1})
    output_data.append({'FieldSize': 'Inf', 'FailureRate': perfect_rate})

    failure_rates_0_8.append(rate_8)
    failure_rates_0_4.append(rate_4)
    failure_rates_0_2.append(rate_2)
    failure_rates_0_1.append(rate_1)
    perfect_rates.append(perfect_rate)

with open('binomial_output.csv', 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=employee_info)
    writer.writeheader()
    writer.writerows(output_data)

plt.plot(redundancies, failure_rates_0_8,
         '*',
         label='Calculated GF(2^8)', alpha=alpha)
plt.plot(redundancies, failure_rates_0_4, '--',
         label='Calculated GF(2^4)', alpha=alpha)
plt.plot(redundancies, failure_rates_0_2, '--',
         label='Calculated GF(2^2)', alpha=alpha)
plt.plot(redundancies, failure_rates_0_1,
         '--', label='Calculated GF(2^1)', alpha=alpha)
plt.plot(redundancies, perfect_rates,
         label='Perfect GF', alpha=alpha)

# PLOT THE P-Rate
# pfunc1 = []
# pfunc2 = []
# pfunc3 = []
# pfunc4 = []
# packets = range(0, threshold+delta_max+1)
# for m in packets:
#     val = P(m, threshold, 0, pow(2, 8))
#     val2 = P(m, threshold, 0, pow(2, 4))
#     val3 = P(m, threshold, 0, pow(2, 2))
#     val4 = P(m, threshold, 0, pow(2, 1))
#     print(m, threshold, val, val2, val3, val4)
#     pfunc1.append(val)
#     pfunc2.append(val2)
#     pfunc3.append(val3)
#     pfunc4.append(val4)

# plt.plot(packets, pfunc1, label='2^8')
# plt.plot(packets, pfunc2, label='2^4')
# plt.plot(packets, pfunc3, label='2^2')
# plt.plot(packets, pfunc4, label='2^1')


# plt.plot(redundancies, failure_rates_2, '-.', label='Failure R=2', alpha=alpha)
# plt.plot(redundancies, paper_values, '--', label='Paper Values R=2 GF(2^8)', alpha=alpha)

plt.grid(True)
plt.legend()
plt.xlabel('Redundant packet count')
plt.ylabel('Decoding Failure Probability')
plt.title("Decoding Failure vs Redundancy (n=16, N=26, PER=0.2")
plt.show()

exit(0)

# BINOMIAL TESTS BELOW

# setting the values
# of n and p
n = 6
p = 0.6
# defining the list of r values
r_values = list(range(n + 1))
# obtaining the mean and variance
mean, var = binom.stats(n, p)
# list of pmf values
dist = [binom.pmf(r, n, p) for r in r_values]
# printing the table
print("r\tp(r)")
for i in range(n + 1):
    print(str(r_values[i]) + "\t" + str(dist[i]))
# printing mean and variance
print("mean = "+str(mean))
print("variance = "+str(var))

# setting the values
# of n and p
fig, axs = plt.subplots(4)
n = 40
p = 0.2
loc = 20
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values]
# plotting the graph
axs[0].set_title("PER 20%")
axs[0].stem(r_values, dist)
plt.show(block=False)
p = 0.4
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values]
# plotting the graph
axs[1].set_title("PER 40%")
axs[1].stem(r_values, dist)
p = 0.5
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values]
# plotting the graph
axs[2].set_title("PER 50%")
axs[2].stem(r_values, dist)
p = 0.6
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values]
# plotting the graph
axs[3].set_title("PER 60%")
axs[3].stem(r_values, dist)
axs[0].set_ylim(0, 1.0)
axs[1].set_ylim(0, 1.0)
axs[2].set_ylim(0, 1.0)
axs[3].set_ylim(0, 1.0)
plt.tight_layout()
plt.ylim(0, 1.0)
plt.show()
