import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np
print(os.getcwd())

# 128 64 32 16
read_size = 1024 * 16
# --serial 066BFF323338424E43042719
# subprocess.run(
#     f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe read ..\\data\\nucleo 0x08020000 131072", shell=True, check=True)

nullword = ['0xFF', '0xFF', '0xFF', '0xFF']
nullword_bytes = bytes([int(x, 0) for x in nullword])


def signed8(value):
    return -(value & 0x80) | (value & 0x7f)


def equals_nullword(bytestring):
    return bytestring == nullword_bytes


def index_to_time(index, rate):
    return index / rate / 60


def plot_file(path, title, rate):
    # path = "../data/nucleo"
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
        elif sequence_number-last_seq_number > 250:
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

            data_time = index_to_time(sequence_number, rate)
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
    l4 = ax4.plot(data_indices_time, sequence_number_set,
                  label='sequence_numbers')
    ax3.legend(handles=l3+l4)
    ax3.set_title("PER over time")
    ax3.set_xlabel('Time (min)')

    l1 = ax1.plot(data_indices_time, data_set_rrsi,
                  color='orange', label='RSSI')
    l2 = ax2.plot(data_indices_time, data_set_snr, label='SNR')
    ax1.legend(handles=l1+l2)
    ax1.set_xlabel('Time (min)')
    ax1.set_title(title)
    ax1.set_ylabel("RSSI [dBm]")
    ax2.set_ylabel("SNR [dB]")

    fig.tight_layout()  # otherwise the right y-label is slightly clipped
    plt.show(block=False)


if __name__ == '__main__':
    base = "G:/My Drive/Study/Thesis/Mar 2022/Datasets/"

    path1 = base+"3_a2"
    title1 = "RSSI and SNR Floor 1 East(Window)"
    rate1 = 0.25
    plot_file(path1, title1, rate1)
    path2 = base+"3_a3"
    title2 = "RSSI and SNR Floor 2 East(Window)"
    rate2 = 0.25
    plot_file(path2, title2, rate2)
    path3 = base+"3_a4"
    title3  = "RSSI and SNR Floor 3 East(Coffee)"
    rate3 = 0.25
    plot_file(path3, title3, rate3)
    path4 = base+"3_a6"
    title4 = "RSSI and SNR Floor 4 East(Coffee)"
    rate4 = 0.25
    plot_file(path4, title4, rate4)
    path5 = base+"3_a5"
    title5 = "RSSI and SNR Floor 5 Roam"
    rate5 = 0.25
    plot_file(path5, title5, rate5)
plt.show()
