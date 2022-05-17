from math import comb
import numpy as np
from scipy.stats import binom
import matplotlib.pyplot as plt

# PER = 0.1
# delta_max = 2
# min = 10
# N = min + delta_max

# x_axis = range(1, 13)
# binomial_pmf = []
# for x in x_axis:
#     val = binom.pmf(x, N, 1.0-PER)
#     binomial_pmf.append(val)

# success_cdf = []
# for x in x_axis:
#     if (x < min):
#         success_cdf.append(0)
#         continue

#     if (x >= min):
#         # cdf = 0
#         # for y in range(x-1, N):
#         #     cdf += binomial_pmf[y]

#         success_cdf.append(1 - binom.cdf(x-1, N, 1.0-PER))
# print(x_axis)

# plt.bar(x_axis, success_cdf)


def P(m, n, r):
    p = 1.0
    for i in range(0, n+r):
        p *= (1 - 1 / pow(2, m-i))
    return p


def success_rate(n, N, eps, r):
    p_success = 0
    p_success_perfect = 0
    for m in range(n, N+1):
        outer_decoder_chance = P(m, n, r)
        print(m, N, outer_decoder_chance)
        p_success += comb(N, m) * pow(eps, N - m) * pow(1-eps, m) * outer_decoder_chance
        p_success_perfect += comb(N, m) * pow(eps, N - m) * pow(1-eps, m)

    return p_success, p_success_perfect


paper_values = [1, 0.99, 0.97,0.95, 0.87, 0.77, 0.66, 0.54, 0.41, 0.295, 0.21]
PER = 0.2
delta_max = 10
threshold = 16
redundancies = range(0, delta_max+1)
failure_rates = []
failure_perfect = []
failure_rates_0 = []
failure_perfect_0 = []
for delta in redundancies:
    total_sent = threshold+delta
    success, success_perfect = success_rate(threshold, total_sent, PER, 2)
    success_0, success_perfect_0 = success_rate(threshold, total_sent, PER, 0)
    failure_rates.append(1-success)
    failure_rates_0.append(1-success_0)
    failure_perfect_0.append(1- success_perfect_0)
    failure_perfect.append(1-success_perfect)

plt.plot(redundancies, failure_rates, label='Failure R=2')
plt.plot(redundancies, failure_perfect, label='Perfect R=2')
plt.plot(redundancies, failure_rates_0, label='Failure R=0')
plt.plot(redundancies, failure_perfect_0, label='Perfect R=0')
plt.plot(redundancies, paper_values, label='Fulcrum (r=2)')
plt.grid(True)
plt.legend()
plt.xlabel('Redundant Packets')
plt.ylabel('Failure Probability')
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
