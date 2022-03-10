import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np
print(os.getcwd())

# 128 64 32 16
read_size = 1024 * 16
# subprocess.run(
#     f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe read ..\\data\\nucleo 0x08020000 131072", shell=True, check=True)

nullword = ['0xFF', '0xFF', '0xFF', '0xFF']
nullword_bytes = bytes([int(x, 0) for x in nullword])

RATE = 0.5  # message per sec


def signed8(value):
    return -(value & 0x80) | (value & 0x7f)


def equals_nullword(bytestring):
    return bytestring == nullword_bytes


def index_to_time(index):
    return index / RATE / 60


path = "G:/My Drive/Study/Thesis/Mar 2022/Datasets/4_a2"
path2 = "../data/nucleo"
file = open(path, "rb")
header = file.read(4)
reserved1 = file.read(4)
reserved2 = file.read(4)
reserved3 = file.read(4)

word = file.read(4)
counter = 0
last_seq_number = None
cum_seq_missed = 0
data_indices_time = []
PER_set = []
sequence_number_set = []
data_set_rrsi = []
data_set_snr = []
while word:

    if equals_nullword(word):
        print("Empty word found. Done.")
        break

    # Process word into measurement
    sequence_number = word[3] << 8 | word[2]
    if last_seq_number is None:
        last_seq_number = sequence_number
    if last_seq_number > sequence_number:
        print(
            f"Last sequence {last_seq_number} number exceeds current {sequence_number}. Considering dropped.")
    elif sequence_number-last_seq_number > 1000:
        print(
            f"Last sequence {last_seq_number} number differentiated with more than 1000 compared to current {sequence_number}. Considering dropped.")
    else:
        seq_diff = sequence_number - last_seq_number

        rssi = word[1]-150
        snr = signed8(word[0])

        # print(sequence_number, counter, snr, rssi)

        if seq_diff > 1:
            print("Packet count missing", seq_diff-1)
            cum_seq_missed += seq_diff - 1

        data_set_rrsi.append(rssi)
        data_set_snr.append(snr)
        sequence_number_set.append(sequence_number)
        PER_set.append(cum_seq_missed/(sequence_number+1))

        data_time = index_to_time(sequence_number)
        data_indices_time.append(data_time)
    # Iterate
    word = file.read(4)
    last_seq_number = sequence_number
    counter += 1

print(f"{counter} measurements found, total packets missed {cum_seq_missed}")

fig, axs = plt.subplots(2)
ax1 = axs[0]
ax2 = ax1.twinx()

ax3 = axs[1]
l3 = ax3.plot(data_indices_time, PER_set, color='orange', label='PER')
ax4 = ax3.twinx()
l4 = ax4.plot(data_indices_time, sequence_number_set, label='sequence_numbers')
ax3.legend(handles=l3+l4)
ax3.set_title("PER over time")

l1 = ax1.plot(data_indices_time, data_set_rrsi,
              color='orange', label='RSSI')
l2 = ax2.plot(data_indices_time, data_set_snr, label='SNR')
ax1.legend(handles=l1+l2)
ax1.set_xlabel('Time (min)')
ax1.set_title("RSSI and SNR EEMCS (In->Outside) SF7 P_TX=14dBm")
ax1.set_ylabel("RSSI [dBm]")
ax2.set_ylabel("SNR [dB]")

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()
