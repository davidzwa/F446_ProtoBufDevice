from scipy.stats import binom
import matplotlib.pyplot as plt
# setting the values
# of n and p
n = 6
p = 0.6
# defining the list of r values
r_values = list(range(n + 1))
# obtaining the mean and variance 
mean, var = binom.stats(n, p)
# list of pmf values
dist = [binom.pmf(r, n, p) for r in r_values ]
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
dist = [binom.cdf(r, n, p, loc) for r in r_values ]
# plotting the graph 
axs[0].set_title("PER 20%")
axs[0].stem(r_values, dist)
plt.show(block=False)
p = 0.4
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values ]
# plotting the graph 
axs[1].set_title("PER 40%")
axs[1].stem(r_values, dist)
p = 0.5
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values ]
# plotting the graph 
axs[2].set_title("PER 50%")
axs[2].stem(r_values, dist)
p = 0.6
# defining list of r values
r_values = list(range(n + 1))
# list of pmf values
dist = [binom.cdf(r, n, p, loc) for r in r_values ]
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
