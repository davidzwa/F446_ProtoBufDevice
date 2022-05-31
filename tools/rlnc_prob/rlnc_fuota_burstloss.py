from statistics import mean
from shared import P, decide_simple, calculate_burst_timeseries
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


class RlncDecisionFactory():
    q = pow(2, 8)

    def __init__(self,
                 gen_threshold,
                 gen_redundancy,
                 PER=None
                 ) -> None:
        self.G = gen_threshold
        self.delta_max = gen_redundancy

        self.current_generation = 0
        self.current_fragment = 0
        self.received = 0
        self.lost = 0
        self.gen_log = pd.DataFrame({'GenerationIndex': [],
                                     'RedundancyUsed': [],
                                     'Success': [],
                                     'Received': [],
                                     'Lost': [],
                                    #  'GFErr': [],
                                     'PER': []})

        # If PER is known we can construct a LUT
        # if PER is not None:
        #     self.probabilities = success_rates(
        #         self.G, self.delta_max, PER, self.q, True)
        # else:
        #     self.probabilities = None

    def __total(self):
        return self.G + self.delta_max

    def switch_gen(self):
        # gen_success_prob = P(
        #     self.current_fragment + 1, self.G, 0, self.q)
        # gen_success_prob_perc = 100.0 * gen_success_prob
        gen_success = 0
        if self.received >= self.G:
            #     gen_success = decide_simple(gen_success_prob)
            gen_success = 1
        # else:
        #     gen_success_prob = 0
        #     gen_success_prob_perc = 0

        # print(
        #     f"RX: {self.received} Err: {self.lost} Gen: {gen_success} (Prob:{gen_success_prob_perc:.1f}%)")

        redundancy_used = self.lost \
            if self.received >= self.G else self.delta_max
        PER = self.lost / (self.received + self.lost)
        row = [self.current_generation,
               redundancy_used,
               gen_success,
               self.received, self.lost,
               #    gen_success_prob_perc,
               PER]

        length = len(self.gen_log.index)
        self.gen_log.loc[length] = row

        self.received = 0
        self.lost = 0
        self.current_generation += 1

    def decide_prob(self, PER):
        """Generate the dynamic probability of successful decoding"""

        # print("Deciding", self.current_fragment, self.__total(), self.current_fragment % self.__total())

        result = decide_simple(PER)
        if result:
            self.received += 1
        else:
            self.lost += 1

        self.current_fragment += 1
        if self.current_fragment % self.__total() == 0:
            self.switch_gen()

        return result


gens = 1200
G = 20
delta = 3
count = gens * G * (1+delta)

xmin = -2  # Heavy bursts, low frequency p=0.1 r=0.15
xmax = 0  # Slight bursts, high frequency p=0.4 r=0.6
xcount = 250
h = 0  # 100% PER
k = 1  # 0% PER
pi_b = 0.1  # % burst PER
xrange = np.logspace(xmin, xmax, num=xcount)
results = None

read_csv = False

if read_csv:
    results = pd.read_csv('27_burst_resistance.csv')
else:
    results = pd.DataFrame({
        'x': [],
        'SuccessRate': [],
        'PER': [],
        'RedundancyUsedMin': [],
        'RedundancyUsed': [],
        'RedundancyUsedMax': []
    })

    for x in xrange:
        print(f'Running x {x:.5f}')
        p = x * pi_b  # move to burst prob
        r = x * (1-pi_b)  # move to good prob (stays stuck)

        # Reset the rng decider
        delta_max = G * (delta)
        decider = RlncDecisionFactory(G, delta_max)

        steps, samples, bs, be, bdiff = calculate_burst_timeseries(
            count, p, r, h, k, PER_decider=decider.decide_prob)

        result_experiment = decider.gen_log
        # print(decider.gen_log)
        suc = mean(result_experiment['Success'])
        per = mean(result_experiment['PER'])
        min_red = 100 * min(result_experiment['RedundancyUsed']) / G
        mean_red = 100 * mean(result_experiment['RedundancyUsed']) / G
        max_red = 100 * max(result_experiment['RedundancyUsed']) / G
        print(f"{x:.4f} {suc:.2f} {min_red:.1f} {mean_red:.1f} {max_red:.1f}")

        row = [x,
               suc,
               per,
               min_red,
               mean_red,
               max_red
               ]

        length = len(results.index)
        results.loc[length] = row

    results.to_csv('27_burst_resistance.csv')

fig, ax1 = plt.subplots()
per_perc = pi_b * 100
plt.title(f"Decoding Burst Resistance (n=20,N=80,PER={per_perc:.0f}%)")
plt.grid(True)
plt.xlabel('Burst Frequency/Duration coefficient (x)')
plt.xscale('log')
p1 = ax1.plot(results.loc[:, "x"], results.loc[:, "RedundancyUsedMin"],
              '-',
              linewidth=0.3,
              color='darkblue', label="Redundancy Used (min)")[0]
p11 = ax1.plot(results.loc[:, "x"], results.loc[:, "RedundancyUsed"],
               '-', color='blue', linewidth=0.2, label="Redundancy Used (mean)")[0]
p12 = ax1.plot(results.loc[:, "x"], results.loc[:, "RedundancyUsedMax"],
               '-', color='black', linewidth=0.3, label="Redundancy Used (max)")[0]

plt.legend()
plt.ylabel('Required Redundancy [%]')
ax2 = ax1.twinx()
p2 = ax2.plot(results.loc[:, "x"], results.loc[:, "SuccessRate"],
              '-', linewidth=0.3, color='green', label="Success Rate")[0]
plt.plot(results.loc[:, "x"], results.loc[:,
                                          "PER"], '-', color='red', linewidth=0.3, label="Temporal PER")[0]
plt.ylabel('Success Rate [%]')
ax1.yaxis.label.set_color(p1.get_color())
ax2.yaxis.label.set_color(p2.get_color())

plt.legend()
plt.savefig('27_burst_resistance.pdf')

plt.figure(2)
plt.title("PER disitribution (40% PER expected)")
plt.hist(results.loc[:, "PER"], density=True)
plt.xlabel("Temporal PER [%]")
plt.ylabel("Density")
plt.savefig('27_burst_resistance_PER_hist.pdf')
# plt.show()
print(results)
