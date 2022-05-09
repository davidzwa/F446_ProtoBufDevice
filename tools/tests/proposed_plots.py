import matplotlib.pyplot as plt
import random
# import numpy as np

random.seed(0)
sample_count = 500
rssi_spread = 15
rssi_max = -90
rssi_lim_max = -60
rssi_lim_min = -150
snr_max = 7
snr_spread = 5
snr_lim_max = 20
snr_lim_min = -20
loss_min = 0
loss_max = 30
lim_loss = False

# Prints list of random items of given length
# list1 = range(0, sample_count)
# samples = sample(list1, 15)
# samples.sort()
# print(samples)
# exit(0)


def random_drops(k):
    samples = [0]
    
    list1 = range(1, sample_count)
    samples += random.sample(list1, k)
    samples.sort()    

    if (samples[-1] != 500):
        samples.append(500)

    return samples, range(0, len(samples))


def random_rssi(count: int, offset):
    rssi_vector = []
    for i in range(0, count):
        n = random.randrange(rssi_max-rssi_spread, rssi_max) + offset
        rssi_vector.append(n)

    return rssi_vector


def random_snr(count: int, offset):
    snr_vector = []
    for i in range(0, count):
        n = random.randrange(snr_max-snr_spread, snr_max) + offset
        snr_vector.append(n)

    return snr_vector


rssi1 = random_rssi(sample_count, 0)
snr1 = random_snr(sample_count, 0)
drops1, drops_y1 = random_drops(2)
rssi2 = random_rssi(sample_count, -10)
snr2 = random_snr(sample_count, -5)
drops2, drops_y2 = random_drops(5)
rssi3 = random_rssi(sample_count, -30)
snr3 = random_snr(sample_count, -12)
drops3, drops_y3 = random_drops(20)
rssi4 = random_rssi(sample_count, -40)
snr4 = random_snr(sample_count, -17)
drops4, drops_y4 = random_drops(50)

f, axes = plt.subplots(3, 4)
col = 0
axis = axes[0, col]
axis.plot(rssi1)
axis.set_title("RSSI for node 1")
axis.set_xlabel("Sample index")
axis.set_ylabel('RSSI [dBm]')
axis.set_ylim([rssi_lim_min, rssi_lim_max])
axis = axes[1, 0]
axis.plot(snr1)
axis.set_title("SNR for node 1")
axis.set_xlabel("Sample index")
axis.set_ylabel('SNR1 [dB]')
axis.set_ylim([snr_lim_min, snr_lim_max])
axis = axes[2, 0]
axis.stem(drops1, drops_y1)
axis.set_title("Frames lost")
axis.set_ylabel("Loss (#)")
if lim_loss:
    axis.set_ylim([loss_min, loss_max])

col = 1
axis = axes[0, col]
axis.plot(rssi2)
axis.set_title("RSSI for node 2")
axis.set_xlabel("Sample index")
axis.set_ylabel('RSSI2 [dBm]')
axis.set_ylim([rssi_lim_min, rssi_lim_max])
axis = axes[1, col]
axis.plot(snr2)
axis.set_title("SNR for node 2")
axis.set_xlabel("Sample index")
axis.set_ylabel('SNR2 [dB]')
axis.set_ylim([snr_lim_min, snr_lim_max])
axis = axes[2, col]
axis.stem(drops2, drops_y2)
axis.set_title("Frames lost")
axis.set_ylabel("Loss (#)")
if lim_loss:
    axis.set_ylim([loss_min, loss_max])

col = 2
axis = axes[0, col]
axis.plot(rssi3)
axis.set_title("RSSI for node 3")
axis.set_xlabel("Sample index")
axis.set_ylabel('RSSI3 [dBm]')
axis.set_ylim([rssi_lim_min, rssi_lim_max])
axis = axes[1, col]
axis.plot(snr3)
axis.set_title("SNR for node 3")
axis.set_xlabel("Sample index")
axis.set_ylabel('SNR2 [dB]')
axis.set_ylim([snr_lim_min, snr_lim_max])
axis = axes[2, col]
axis.stem(drops3, drops_y3)
axis.set_title("Frames lost")
axis.set_ylabel("Loss (#)")
if lim_loss:
    axis.set_ylim([loss_min, loss_max])

col = 3
axis = axes[0, col]
axis.plot(rssi4)
axis.set_title("RSSI for node 4")
axis.set_xlabel("Sample index")
axis.set_ylabel('RSSI3 [dBm]')
axis.set_ylim([rssi_lim_min, rssi_lim_max])
axis = axes[1, col]
axis.plot(snr4)
axis.set_title("SNR for node 4")
axis.set_xlabel("Sample index")
axis.set_ylabel('SNR2 [dB]')
axis.set_ylim([snr_lim_min, snr_lim_max])
axis = axes[2, col]
axis.stem(drops4, drops_y4)
axis.set_title("Frames lost")
axis.set_ylabel("Loss (#)")
if lim_loss:
    axis.set_ylim([loss_min, loss_max])

# col = 4
# axis = axes[0, col]
# axis.plot(rssi3)
# axis.set_title("RSSI for node 3")
# axis.set_xlabel("Sample index")
# axis.set_ylabel('RSSI3 [dBm]')
# axis.set_ylim([rssi_lim_min, rssi_lim_max])
# axis = axes[1, col]
# axis.plot(snr3)
# axis.set_title("SNR for node 3")
# axis.set_xlabel("Sample index")
# axis.set_ylabel('SNR2 [dB]')
# axis.set_ylim([snr_lim_min, snr_lim_max])
# axis = axes[2, col]
# axis.stem(drops3, drops_y3)
# axis.set_title("Frames lost")
# axis.set_ylabel("Loss (#)")
# if lim_loss:
#     axis.set_ylim([loss_min, loss_max])
    
plt.tight_layout()
plt.show()
