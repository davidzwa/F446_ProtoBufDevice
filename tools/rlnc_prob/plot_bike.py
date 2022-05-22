import sys
sys.path.append("..")
import matplotlib.pyplot as plt
import pandas as pd

from shared import find_erasures

PER = 0.2
delta_max = 60
threshold = 20
q = pow(2, 8)
csv_file = 'range_test/Bike-test/Bike_test_SF8_experiment_phy_2022-05-07_13-38-44.csv'
df = pd.read_csv(csv_file)

seqs = df["SequenceNumber"]
first = seqs.iat[0]
last = seqs.iat[-1]
received = len(seqs) - first
per = 100.0 * (last - received) / (last - first)
print(f"FIRST: {first} LAST: {last} RX: {received}")
print(f"TOTAL PER: {per: .2f}%")

find_erasures(seqs, 10)
