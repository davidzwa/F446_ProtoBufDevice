from shared import find_erasures
import pandas as pd
import matplotlib.pyplot as plt
from stlink_flash_convert import plot_erasures_PER

alpha = 0.15
marker_size = 1


def plot_file(csv_path, rate, title):
    df = pd.read_csv(csv_path)
    rssis = df["Rssi"]
    snrs = df["Snr"]
    seqs = df["SequenceNumber"]
    first = seqs.iat[0]
    last = seqs.iat[-1]
    received = len(seqs) - first
    per = 100.0 * (last - received) / (last - first)
    print(f"FIRST: {first} LAST: {last} RX: {received}")
    print(f"TOTAL PER: {per: .2f}%")

    plot_erasures_PER(alpha, marker_size, seqs.values, rssis, snrs,
                      title, rate, PER_filter)


csv_file_sf8 = 'range_test/Bike-test/Bike_test_SF8_experiment_phy_2022-05-07_13-38-44.csv'
csv_file_sf9 = 'range_test/Bike-test/Bike_test_SF9_experiment_phy_2022-05-07_13-52-50.csv'
csv_file_sf10 = 'range_test/Bike-test/Bike_test_SF10_experiment_phy_2022-05-07_13-56-49.csv'
csv_file_sf11 = 'range_test/Bike-test/Bike_test_SF11_experiment_phy_2022-05-07_14-03-46.csv'

rate = 20
PER_filter = 51

plot_file(csv_file_sf8, 10, "Bike Range Test PER (SF8)")
plt.savefig('27_SF8_bike.pdf')
plot_file(csv_file_sf9, 10, "Bike Range Test PER (SF9)")
plot_file(csv_file_sf10, 10, "Bike Range Test PER (SF10)")
plot_file(csv_file_sf11, 10, "Bike Range Test PER (SF11)")

plt.show()
