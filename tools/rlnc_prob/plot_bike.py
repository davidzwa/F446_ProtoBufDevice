import pandas as pd
import matplotlib.pyplot as plt
from stlink_flash_convert import plot_erasures_PER

alpha = 0.15
marker_size = 0.5
plt_index = 1

def plot_file(csv_path, rate, title):
    global plt_index
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
    plt.figure(plt_index)
    plot_erasures_PER(alpha, marker_size, seqs.values, rssis, snrs,
                      title, rate, PER_filter)
    
    plt_index +=1


csv_file_sf8 = 'range_test/Bike-test/Bike_test_SF8_experiment_phy_2022-05-07_13-38-44.csv'
csv_file_sf9 = 'range_test/Bike-test/Bike_test_SF9_experiment_phy_2022-05-07_13-52-50.csv'
csv_file_sf10 = 'range_test/Bike-test/Bike_test_SF10_experiment_phy_2022-05-07_13-56-49.csv'
csv_file_sf11 = 'range_test/Bike-test/Bike_test_SF11_experiment_phy_2022-05-07_14-03-46.csv'

rate = 20
PER_filter = 201

s = 60
plot_file(csv_file_sf8, 10, "Bike Range Test PER (SF8, $P_{TX}$=+14dBm, BW=500kHz)")
plt.plot([0.0, s*0.1], [800,800], color='green', marker='o', linestyle='dashed',
     linewidth=1, markersize=2)
plt.text(s*0.045, 1050, "Stable")

plt.plot([s*0.14, s*0.155], [3500, 3500], color='orange', marker='o', linestyle='dashed',
         linewidth=1, markersize=2)
plt.text(s*0.137, 3750, "Lossy")

plt.plot([s*0.165, s*0.18], [2250, 2250], color='red', marker='o', linestyle='dashed',
         linewidth=1, markersize=2)
plt.text(s*0.164, 1700, "Loss")

plt.plot([s*0.185, s*0.245], [2500, 2500], color='purple', marker='o', linestyle='dashed',
         linewidth=1, markersize=2)
plt.text(s*0.205, 2750, "Outage")

# plt.scatter(0.15, )
plt.savefig('27_SF8_bike.pdf')
# plot_file(csv_file_sf9, 10, "Bike Range Test PER (SF9)")
# plot_file(csv_file_sf10, 10, "Bike Range Test PER (SF10)")
# plot_file(csv_file_sf11, 10, "Bike Range Test PER (SF11)")
