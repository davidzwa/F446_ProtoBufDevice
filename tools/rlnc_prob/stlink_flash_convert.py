import os
import matplotlib.pyplot as plt
import numpy as np

from shared import meanfilt, find_erasures, parse_flash_file
print(os.getcwd())

# 128 64 32 16
# read_size = 1024 * 16
# --serial 066BFF323338424E43042719
# subprocess.run(
#     f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe read ..\\data\\nucleo 0x08040000 131072", shell=True, check=True)

rlnc_sequence_numbers = True
PER_datasets = []
alpha = 0.15
marker_size = 1


def plot_file(path, title, rate, PER_filter):
    sequence_numbers, rssis, snrs = parse_flash_file(path)

    timestrings, erasures, counter, last_seq_number, packets_missed, resets = find_erasures(
        sequence_numbers, rate)

    print("First seq", sequence_numbers[0])
    print("Last seq", sequence_numbers[-1])
    print(len(erasures), "erasure/reception entries")
    print(f"{counter} measurements found, total packets missed {packets_missed}, resets {resets}")

    PER_output = meanfilt(np.array(erasures), PER_filter)
    step = 1/rate/3600
    erasure_indices = np.arange(0, timestrings[-1] + step, step)
    print("PER mean length", len(erasure_indices), len(PER_output))

    fig, axs = plt.subplots(2)
    ax1 = axs[0]
    ax2 = ax1.twinx()

    ax3 = axs[1]
    l3 = ax3.scatter(erasure_indices, PER_output,
                     s=2,
                     color='orange', label='PER')
    ax3.set_ylim([0, 1])
    ax3.text(1.5, 0.1, "PER")
    ax4 = ax3.twinx()
    l4 = ax4.scatter(timestrings, sequence_numbers,
                     s=marker_size,
                     label='sequence_numbers')
    ax4.text(3, 4000, "Seq")
    # ax3.legend(handles=l3+l4)
    ax3.set_title("PER over time")
    ax3.set_xlabel('Time (h)')

    l1 = ax1.scatter(timestrings, rssis,
                     color='orange',
                     alpha=alpha,
                     s=marker_size,
                     label='RSSI')
    ax1.text(1, -95, "RSSI")
    l2 = ax2.scatter(timestrings, snrs,
                     alpha=alpha,
                     s=marker_size,
                     label='SNR')
    ax2.text(2, -7, "SNR")
    # ax1.legend(handles=l1+l2)
    ax1.set_xlabel('Time (h)')
    ax1.set_title(title)
    ax1.set_ylabel("RSSI [dBm]")
    ax2.set_ylabel("SNR [dB]")

    fig.tight_layout()  # otherwise the right y-label is slightly clipped

    plt.show(block=False)

    return PER_output


if __name__ == '__main__':
    # base1 = "../data/nucleo"
    base = "D:/Projects/f446-lora/data/datasets/"

    # path0 = base
    # title0 = "RSSI and SNR Roaming"
    # rate0 = 0.5
    # PER_set1 = plot_file(path0, title0, rate0)
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

    PER_filter_size = 21
    path3 = base+"4_a4"
    title3 = "RSSI and SNR Floor 3 East (Coffee machine)"
    rate3 = 0.25
    PER_set3 = plot_file(path3, title3, rate3, PER_filter_size)
    PER_datasets.append(PER_set3)

    path4 = base+"4_a6"
    title4 = "RSSI and SNR Floor 4 East (Coffee machine)"
    rate4 = 0.25
    PER_set4 = plot_file(path4, title4, rate4, PER_filter_size)
    PER_datasets.append(PER_set4)

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
    plt.show()
    # plt.show()
