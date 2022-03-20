from msilib import sequence
import os
import subprocess
from typing import ByteString
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
PER_datasets = []


def signed8(value: int) -> int:
    return -(value & 0x80) | (value & 0x7f)


def equals_nullword(bytestring: ByteString) -> bool:
    return bytestring == nullword_bytes


def index_to_time(index: int, rate: float) -> float:
    return index / rate / 60 / 60


def parse_binary(path: str) -> dict():
    file = open(path, "rb")

    # Removes the unused header from data
    header = file.read(4)
    reserved1 = file.read(4)
    reserved2 = file.read(4)
    reserved3 = file.read(4)

    word = file.read(4)

    sequence_numbers = []
    rssi = []
    snr = []

    counter = 0
    while word:
        if equals_nullword(word):
            print("Empty word found. Done.")
            break

        sequence_number = word[3] << 8 | word[2]
        sequence_numbers.append(sequence_number)
        rssi.append(word[1]-150)
        snr.append(signed8(word[0]))

        word = file.read(4)
        counter += 1

    return {
        "sequence_numbers": sequence_numbers,
        "rssi": rssi,
        "snr": snr
    }


def filter_wrong_sequence_numbers(data: dict) -> dict():
    count = len(data["sequence_numbers"])
    data["packets_missed"] = 0
    data["packets_faulty_count"] = 0
    data["packets_faulty"] = []

    for i in range(0, count):
        if i >= (count-data["packets_faulty_count"]-1):
            print("BREAK", i, count-data["packets_faulty_count"]-1, data["packets_faulty_count"], len(data["sequence_numbers"]))
            break
        if i > 0:
            prev = data["sequence_numbers"][i-1]
            current = data["sequence_numbers"][i]
            if i+1 >= count-1:
                break

            next = data["sequence_numbers"][i+1]
            if not (prev < current < next):
                if next <= current:
                    print("Fault Next", prev, current, next)
                    data["sequence_numbers"].pop(i+1)
                elif current <= prev:
                    print("Fault Current", prev, current, next)
                    data["sequence_numbers"].pop(i)
                else:
                    print("Fault other", prev, current, next)
                data["packets_faulty"].append(i)
                data["packets_faulty_count"] += 1
                continue

            diff = current-prev-1
            if diff is not 0:
                print(i, current, diff)
                data["packets_missed"] += diff
    return data


def plot_file(path, title, rate):
    data = parse_binary(path)

    return filter_wrong_sequence_numbers(data)

    # counter = 0
    # last_seq_number = None
    # cum_seq_missed = 0
    # data_indices_time = []
    # PER_set = []
    # sequence_number_set = []
    # data_set_rrsi = []
    # data_set_snr = []

    #    # Process word into measurement
    #    if last_seq_number is None:
    #         last_seq_number = sequence_number
    #     if last_seq_number > sequence_number:
    #         print(
    #             f"Last sequence {last_seq_number} number exceeds current {sequence_number}. Considering dropped.")
    #     elif sequence_number-last_seq_number > 250:
    #         print(
    #             f"Last sequence {last_seq_number} number differentiated with more than 1000 compared to current {sequence_number}. Considering dropped.")
    #     else:
    #         seq_diff = sequence_number - last_seq_number

    #         # print(sequence_number, counter, snr, rssi)

    #         if seq_diff > 1:
    #             print("Packet count missing", seq_diff-1)
    #             cum_seq_missed += seq_diff - 1

    #         data_set_rrsi.append(rssi)
    #         data_set_snr.append(snr)
    #         sequence_number_set.append(sequence_number)
    #         PER_set.append(cum_seq_missed/(sequence_number+1))

    #         data_time = index_to_time(sequence_number, rate)
    #         data_indices_time.append(data_time)
    #     # Iterate
    #     word = file.read(4)
    #     last_seq_number = sequence_number
    #     counter += 1

    # print(f"{counter} measurements found, tota1l packets missed {cum_seq_missed}")

    # fig, axs = plt.subplots(2)
    # ax1 = axs[0]
    # ax2 = ax1.twinx()

    # ax3 = axs[1]
    # l3 = ax3.plot(data_indices_time, PER_set, color='orange', label='PER')
    # ax4 = ax3.twinx()
    # l4 = ax4.plot(data_indices_time, sequence_number_set,
    #               label='sequence_numbers')
    # ax3.legend(handles=l3+l4)
    # ax3.set_title("PER over time")
    # ax3.set_xlabel('Time (h)')

    # l1 = ax1.plot(data_indices_time, data_set_rrsi,
    #               color='orange', label='RSSI')
    # l2 = ax2.plot(data_indices_time, data_set_snr, label='SNR')
    # ax1.legend(handles=l1+l2)
    # ax1.set_xlabel('Time (h)')
    # ax1.set_title(title)
    # ax1.set_ylabel("RSSI [dBm]")
    # ax2.set_ylabel("SNR [dB]")

    # fig.tight_layout()  # otherwise the right y-label is slightly clipped
    # plt.show(block=False)

    # return PER_set


if __name__ == '__main__':
    # base1 = "../data/nucleo"
    base = "G:/My Drive/Study/Thesis/Mar 2022/Datasets/"

    path0 = base + "3_a4"
    title0 = "RSSI and SNR Roaming"
    rate0 = 0.5
    data = plot_file(path0, title0, rate0)
    print(data.keys())
    # PER_datasets.append(PER_set1)

    # path1 = base +"3_a2"
    # title1 = "RSSI and SNR Floor 1 East(Window)"
    # rate1 = 0.25
    # PER_set1 = plot_file(path1, title1, rate1)
    # PER_datasets.append(PER_set1)

    # path2 = base+"3_a3"
    # title2 = "RSSI and SNR Floor 2 East(Window)"
    # rate2 = 0.25
    # PER_set2 = plot_file(path2, title2, rate2)
    # PER_datasets.append(PER_set2)

    # path3 = base+"3_a4"
    # title3  = "RSSI and SNR Floor 3 East(Coffee)"
    # rate3 = 0.25
    # PER_set3 = plot_file(path3, title3, rate3)
    # PER_datasets.append(PER_set3)

    # path4 = base+"3_a6"
    # title4 = "RSSI and SNR Floor 4 East(Coffee)"
    # rate4 = 0.25
    # PER_set4 = plot_file(path4, title4, rate4)
    # PER_datasets.append(PER_set4)

    # path5 = base+"3_a5"
    # title5 = "RSSI and SNR Floor 5 Roam"
    # rate5 = 0.25
    # PER_set5 = plot_file(path5, title5, rate5)
    # PER_datasets.append(PER_set5)

    # data = [PER_datasets[0], PER_datasets[1],
    #         PER_datasets[2], PER_datasets[3], PER_datasets[4]]

    # fig = plt.figure(figsize=(10, 7))

    # # Creating axes instance
    # # ax = fig.add_axes([0, 0, 1, 1])
    # plt.title("Packet-Error-Ratio per experiment")
    # plt.ylabel("PER (ratio)")
    # plt.xlabel("Experiment")

    # # Creating plot
    # bp = plt.boxplot(data)

    # show plot
    # fig.tight_layout()
    # plt.show()
    # plt.show()
