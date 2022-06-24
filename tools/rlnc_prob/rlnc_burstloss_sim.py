from math import floor, log
from msilib.schema import Error
from statistics import mean, stdev
from shared import P, decide_simple, calculate_burst_timeseries
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


class RlncDecisionFactory():
    q = pow(2, 8)

    def __init__(self,
                 gen_threshold,
                 gen_delta
                 ) -> None:
        self.G = gen_threshold
        self.delta = gen_delta
        self.delta_max = gen_threshold * gen_delta

        self.current_generation = 0
        self.current_fragment = 0
        self.received = 0
        self.lost = 0

        self.gen_log = pd.DataFrame({'GenerationIndex': [],
                                     'RedundancyUsed': [],
                                     'Success': [],
                                     'SuccessUnmixed': [],
                                     'SuccessSemiUnmixed': [],
                                     'Received': [],
                                     'ReceivedUnmixedStd': [],
                                     'ReceivedUnmixedMean': [],
                                     'ReceivedUnmixedMin': [],
                                     'ReceivedUnmixedMax': [],
                                     'Lost': [],
                                     'ThresholdUnmixed': [],
                                     'ThresholdRptmixed': [],
                                     'PER': []})

        # Reception status of mixed/unmixed approaches
        self.rlnc_threshold = -1
        self.unmixed_threshold = -1
        self.semi_unmixed_threshold = -1
        self.unmixed_reception = [0] * self.G
        self.semi_unmixed_reception = [0] * self.G
        self.shuffled_arrivals = self.shuffle_arrival_indices()
        self.semi_shuffled_arrivals = self.repeat_shuffle_arrival_indices()

    def shuffle_arrival_indices(self):
        elements = range(0, self.G)
        arrivals_shuffled = np.repeat(elements, self.delta+1)
        rng = np.random.default_rng()
        rng.shuffle(arrivals_shuffled)
        assert len(arrivals_shuffled) == self.G * (self.delta+1)
        return arrivals_shuffled

    def repeat_shuffle_arrival_indices(self):
        rng = np.random.default_rng()
        repetition = self.delta + 1
        primitivesA = range(0, floor(self.G / 2))
        primitivesB = range(floor(self.G / 2), self.G)
        arrivals_shuffled = []
        for i in range(0, repetition*2):
            if i % 2 == 0:
                arrivals_shuffled = [*arrivals_shuffled,
                                     *rng.permutation(primitivesA)]
            else:
                arrivals_shuffled = [*arrivals_shuffled,
                                     *rng.permutation(primitivesB)]

        assert (len(primitivesA) + len(primitivesB)) == self.G
        assert len(arrivals_shuffled) == self.G * repetition

        return arrivals_shuffled

    def __total(self):
        return self.G + self.delta_max

    def switch_gen(self):
        gen_success = 0

        # We assume perfect decoding non-linearity
        if self.received >= self.G:
            gen_success = 1

        received_mean = np.mean(self.unmixed_reception)
        received_std = np.std(self.unmixed_reception)
        received_min = np.min(self.unmixed_reception)
        received_max = np.max(self.unmixed_reception)
        success_unmixed = self.__get_unmixed_rank() == len(self.unmixed_reception)
        success_semi_unmixed = self.__get_semi_unmixed_rank() == len(self.semi_unmixed_reception)

        PER = self.lost / (self.received + self.lost)
        row = [self.current_generation,
               self.rlnc_threshold,
               gen_success,  # 'Success'
               success_unmixed,  # 'SuccessUnmixed',
               success_semi_unmixed,
               self.received,
               received_std,
               received_mean,
               received_min,
               received_max,
               self.lost,
               # Rate of redundancy for success (threshold)
               self.unmixed_threshold,
               self.semi_unmixed_threshold,
               PER]

        if self.unmixed_threshold != -1 and not gen_success:
            raise Exception("Cannot succeed Rng when RLNC fails")

        length = len(self.gen_log.index)
        self.gen_log.loc[length] = row

        # Track RLNC stats
        self.received = 0
        self.lost = 0
        self.current_generation += 1

        # Track mixed red stats
        self.rlnc_threshold = -1
        self.unmixed_threshold = -1
        self.unmixed_reception = [0] * self.G
        self.shuffled_arrivals = self.shuffle_arrival_indices()
        self.semi_unmixed_threshold = -1
        self.semi_unmixed_reception = [0] * self.G
        self.semi_shuffled_arrivals = self.repeat_shuffle_arrival_indices()

    def __get_semi_unmixed_rank(self):
        return np.count_nonzero(self.semi_unmixed_reception)

    def __get_unmixed_rank(self):
        return np.count_nonzero(self.unmixed_reception)

    def decide_prob(self, PER):
        """Generate the dynamic probability of successful decoding"""
        error = 0
        if PER > 0:
            error = decide_simple(PER)
        elif PER == 1:
            error = 1

        # Get current 0-indexed generation fragment index (modulo)
        arrival_index = self.current_fragment % self.__total()

        if not error:
            # RLNC tracking
            self.received += 1
            if self.G == self.received and self.rlnc_threshold == -1:
                self.rlnc_threshold = self.lost

            # Retrieve randomized fragment numbers
            sequence_number = self.shuffled_arrivals[arrival_index]
            sequence_number_semi = self.semi_shuffled_arrivals[arrival_index]

            # Track unmixed non-RLNC variants
            self.unmixed_reception[sequence_number] += 1
            self.semi_unmixed_reception[sequence_number_semi] += 1
            mixed_received = self.__get_unmixed_rank()
            mixed_received_semi = self.__get_semi_unmixed_rank()

            # We track semi unmixed threshold success once (not more)
            if self.G == mixed_received_semi and self.semi_unmixed_threshold == -1:
                self.semi_unmixed_threshold = self.lost  # 1-based packet count
                if (self.rlnc_threshold == -1):
                    raise Exception("RLNC cannot fail before semi RNG")

                if (self.semi_unmixed_threshold - self.rlnc_threshold) < 0:
                    raise Exception("RLNC cannot perform worse than semi RNG")

            # We track threshold success once (not more)
            if self.G == mixed_received and self.unmixed_threshold == -1:
                self.unmixed_threshold = self.lost  # 1-based packet count
                if (self.rlnc_threshold == -1):
                    raise Exception("RLNC cannot fail before RNG")

                if (self.unmixed_threshold - self.rlnc_threshold) < 0:
                    raise Exception("RLNC cannot perform worse than RNG")
        else:
            self.lost += 1

        # Precrement
        self.current_fragment += 1

        # Reset before next arrival
        if arrival_index == (self.__total() - 1):
            self.switch_gen()

        return error


gens = 1000
G = 20
delta = 2
count = gens * G * (1+delta)

xmin = -3    # Heavy bursts, low frequency p=0.1 r=0.15
xmax = log(1)       # Slight bursts, high frequency p=0.4 r=0.6
xcount = 100
h = 0  # 0% PRR
k = 1  # 100% PRR
pi_b = 0.6  # % burst PER
# np.logspace(xmin, xmax, num=xcount)
xrange = np.linspace(pow(10, xmin), pow(10, xmax), num=xcount)
results = None

read_csv = False

if read_csv:
    results = pd.read_csv('27_burst_resistance.csv')
else:

    results = pd.DataFrame({
        'x': [],
        'SuccessRate': [],
        'SuccessRateUnmixed': [],
        'SuccessRateSemiUnmixed': [],
        'PER': [],
        'RedundancyUsedMin': [],
        'RedundancyUsed': [],
        'RedundancyUsedMax': [],
        'Lost': [],
        'WorseDiffRngmixedRlnc': [],
        'WorseDiffRepeatmixedRlnc': []
    })

    header_str = "X      Suc MinR AvgR MaxR Lost //        Succ Fls Thr // Diff"
    print(header_str)

    for x in xrange:
        # print(f'Running x {x:.5f}')
        p = x * pi_b  # move to burst prob
        r = x * (1-pi_b)  # move to good prob (stays stuck)

        # Reset the rng decider
        decider = RlncDecisionFactory(G, delta)

        steps, samples, bs, be, bdiff = calculate_burst_timeseries(
            count, p, r, h, k, PER_decider=decider.decide_prob)

        data = decider.gen_log
        suc = mean(data['Success'])
        suc_unmixed = mean(data['SuccessUnmixed'])
        suc_semi_unmixed = mean(data['SuccessSemiUnmixed'])
        per = mean(data['PER'])

        rlnc_thres = data['RedundancyUsed']
        filtered_rlnc_thres = rlnc_thres[rlnc_thres >= 0]

        min_red = 100 * min(filtered_rlnc_thres) / G
        mean_red = 100 * mean(filtered_rlnc_thres) / G
        max_red = 100 * max(filtered_rlnc_thres) / G
        lost_mean = mean(data['Lost'])

        thres = data['ThresholdUnmixed']
        # filtered_thres = thres[thres >= 0]
        mean_thres_unmixed = mean(thres)  # Gotta check this is fair

        both = 0
        rlnc_only = 0
        rng_only = 0
        # non_failures_diffs = []
        # non_failures_ratio = []
        # for index in range(0, len(rlnc_thres)):
        #     rlnc = rlnc_thres[index]
        #     rng = thres[index]
        #     if rlnc == -1 and rng == -1:
        #         both +=1
        #     elif rlnc == -1:
        #         # Rarely/never occurs that RLNC is alone in its failure
        #         rlnc_only +=1
        #     elif rng == -1:
        #         rng_only +=1
        #     else:
        #         non_failures_diffs.append(rlnc - rng)
        #         non_failures_ratio.append(rlnc/rng if rng != 0 else 1)
        # print(both, rlnc_only, rng_only, mean(non_failures))
        # failures_rlnc = len(rlnc_thres) - len(filtered_rlnc_thres)
        # failures_random = len(thres) - len(filtered_thres)
        # print("RLNC Thres fails red.", failures_rlnc, len(filtered_rlnc_thres))
        # print("RNG Thres fails red.", failures_random, len(filtered_thres))

        print(header_str)
        # diff = mean(non_failures_diffs)
        # ratio = 100 * mean(non_failures_ratio)
        suc_diff = suc - suc_unmixed
        suc_semi_diff = suc - suc_semi_unmixed
        ratio = suc/suc_unmixed if suc_unmixed > 0 else 0
        semi_ratio = suc/suc_semi_unmixed if suc_semi_unmixed > 0 else 0
        print(f"{x:.4f} {suc:.2f} {min_red:.1f} {mean_red:.1f} {max_red:.1f} {lost_mean:.1f} // Unmixed {suc_unmixed:.2f} {mean_thres_unmixed:.1f} // Diff {suc_diff:.2f} {ratio:.2f} \
             {suc_semi_diff:.2f} {semi_ratio:.2f} ")

        row = [x,
               suc,
               suc_unmixed,
               suc_semi_unmixed,
               per,
               min_red,
               mean_red,
               max_red,
               lost_mean,
               suc_diff,
               suc_semi_diff
               ]
        length = len(results.index)
        results.loc[length] = row

        results.to_csv('27_burst_resistance.csv')

fig, ax1 = plt.subplots()
per_perc = pi_b * 100
fragment_max = G*(delta+1)
plt.title(
    f"Decoding Burst Resistance (n=20,N={fragment_max},PER={per_perc:.0f}%)")
plt.grid(True)
plt.xlabel('Burst Frequency/Duration coefficient (x)')
# plt.xscale('log')
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

plt.title(f"PER distribution ({per_perc:.0f}% PER expected)")
plt.hist(results.loc[:, "PER"], density=True)
plt.xlabel("Temporal PER [%]")
plt.ylabel("Density")
plt.savefig('27_burst_resistance_PER_hist.pdf')

plt.figure(3)
rlnc = 100*results.loc[:, "SuccessRate"]
unmixed = 100*results.loc[:, "SuccessRateUnmixed"]
semi_unmixed = 100*results.loc[:, "SuccessRateSemiUnmixed"]
diff = 100*(results.loc[:, "WorseDiffRngmixedRlnc"])
plt.title(
    f"Success rate comparison Rngmixed vs Rlnc ({per_perc:.0f}% PER expected)")
plt.plot(results.loc[:, "x"], rlnc, label="Rlnc")
plt.plot(results.loc[:, "x"], unmixed, label="Rngmixed")
plt.plot(results.loc[:, "x"], semi_unmixed, label="Semi-Rngmixed")
plt.xlabel("Burst Frequency/Duration coefficient (x)")
plt.ylabel("Success Rate [%]")
plt.grid()
plt.legend()
plt.savefig('27_burst_resistance_diff.pdf')
plt.savefig('27_burst_resistance_diff.png')
# plt.show()

print(results)
