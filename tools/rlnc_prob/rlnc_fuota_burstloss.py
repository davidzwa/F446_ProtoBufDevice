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
                                     'GFErr': [],
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
        gen_success_prob = P(
            self.current_fragment + 1, self.G, 0, self.q)
        gen_success_prob_perc = 100.0 * gen_success_prob
        gen_success = False
        if self.received >= self.G:
            gen_success = decide_simple(gen_success_prob)
        else:
            gen_success_prob = 0
            gen_success_prob_perc = 0

        # print(
        #     f"RX: {self.received} Err: {self.lost} Gen: {gen_success} (Prob:{gen_success_prob_perc:.1f}%)")

        redudancy_used = self.received - \
            self.G if self.received > self.G else self.delta_max
        PER = self.lost / (self.received + self.lost)
        row = [self.current_generation, redudancy_used, gen_success,
               self.received, self.lost, gen_success_prob_perc, PER]

        length = len(self.gen_log.index)
        self.gen_log.loc[length] = row

        self.received = 0
        self.lost = 0
        self.current_generation += 1

    def decide_prob(self, PER):
        """Generate the dynamic probability of successful decoding"""
        # success_rate = 1.0 - \
        #     failure_rate(self.G, self.current_fragment+1, PER, self.q, True)

        self.current_fragment += 1
        if self.current_fragment % self.__total() == 0:
            self.switch_gen()

        result = decide_simple(PER)
        if result:
            self.received += 1
        else:
            self.lost += 1
        return result


gens = 600
G = 20
delta = 3
count = gens * G * (1+delta)

xmin = 0.05  # Short burst
xmax = 0.5
xrange = np.arange(xmin, xmax, 0.02)

results = pd.DataFrame({
    'x': [],
    'SuccessRate': [],
    'PER': [],
    'Redundancy': []})

for x in xrange:
    print(f'Running x {x:.2f}')
    pi_b = 0.4  # 5% burst
    h = 0  # 100% PER
    k = 1  # 0% PER

    p = x * pi_b  # move to burst prob
    r = x * (1-pi_b)  # move to good prob (stays stuck)

    delta_max = G * (delta)
    decider = RlncDecisionFactory(G, delta_max)
    steps, samples, bs, be, bdiff = calculate_burst_timeseries(
        count, p, r, h, k, PER_decider=decider.decide_prob)

    # results = decider.gen_log
    # print(x, mean(results['Success']), mean(
    #     results['PER']), mean(results['RedundancyUsed']))
    result_experiment = decider.gen_log
    row = [x,
           mean(result_experiment['Success']),
           mean(result_experiment['PER']),
           mean(result_experiment['RedundancyUsed'])]

    length = len(results.index)
    results.loc[length] = row

    print(row)
    plt.scatter([x], 100*(mean(result_experiment['RedundancyUsed']) - G) / G)

# plt.xticks(range(1, len(xrange)+1, 1), xrange)
results.to_csv('27_burst_resistance.csv')

plt.title(f"Decoding Burst Resistance (n=20,N=80)")
plt.savefig('27_burst_sim.pdf')
plt.xlabel('Good/burst ratio (x)')
plt.ylabel('Required Redundancy [%]')
plt.show()
print(results)
