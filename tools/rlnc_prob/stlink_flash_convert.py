import os
import matplotlib.pyplot as plt
import numpy as np

from shared import parse_flash_file, plot_erasures_PER
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


def plot_analysis_file(path, title, rate, PER_filter, file=None):
    sequence_numbers, rssis, snrs = parse_flash_file(path)

    return plot_erasures_PER(np.array(sequence_numbers), 
                             rssis, snrs, 
                             rate=rate, title=title, 
                             PER_filter=PER_filter, 
                             minor_ticks=None, major_ticks=None, 
                             file=file)


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

    PER_filter_size = 41
    path3 = base+"4_a4"
    title3 = "Indoor experiment RSSI and SNR (3rd floor)"
    rate3 = 0.25
    PER_set3 = plot_analysis_file(path3, title3, rate3, PER_filter_size, "30_flash_floor3")
    PER_datasets.append(PER_set3)

    path4 = base+"4_a6"
    title4 = "Indoor experiment RSSI and SNR (4th floor)"
    rate4 = 0.25
    PER_set4 = plot_analysis_file(
        path4, title4, rate4, PER_filter_size, "30_flash_floor4")
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
    # plt.show()
