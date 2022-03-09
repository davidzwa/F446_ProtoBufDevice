import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np
print(os.getcwd())

# 128 64 32 16 
# read_size = 1024 * 16
# subprocess.run(
#     f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe read ..\\data\\nucleo 0x08020000 131072", shell=True, check=True)

nullword = ['0xFF', '0xFF', '0xFF', '0xFF']
nullword_bytes = bytes([int(x, 0) for x in nullword])


def signed8(value):
    return -(value & 0x80) | (value & 0x7f)

def equals_nullword(bytestring):
    return bytestring == nullword_bytes

file = open("../data/nucleo", "rb")
header = file.read(4)
reserved1 = file.read(4)
reserved2 = file.read(4)
reserved3 = file.read(4)

word = file.read(4)
counter = 0
last_seq_number = None
cum_seq_missed = 0
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
    seq_diff = sequence_number - last_seq_number
    
    rssi = word[1]-150
    snr = signed8(word[0])
    print(snr, rssi, sequence_number)
    if seq_diff > 1:
        print("Sequence diff", seq_diff)
        cum_seq_missed += seq_diff - 1
        
    data_set_rrsi.append(rssi) 
    data_set_snr.append(snr)
    
    # Iterate
    word = file.read(4)
    last_seq_number = sequence_number
    counter += 1
                              
print(f"{counter} measurements found, total packets missed {cum_seq_missed}")

fig, ax1 = plt.subplots()
ax1.set_title("Signal strength and SNR ~20m SF7 TX0")
ax1.set_ylabel("RSSI [dBm]")
ax1.boxplot(data_set_rrsi)
ax1.plot(data_set_rrsi)
# ax2 = ax1.twinx()
# ax2.boxplot([2, data_set_snr])
# ax2.set_ylabel("SNR [dBm]")

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()
