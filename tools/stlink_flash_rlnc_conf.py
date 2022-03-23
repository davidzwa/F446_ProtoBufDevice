import os
import subprocess

# .\stlink\stlink-1.7.0-x86_64-w64-mingw32\bin\st-flash.exe --area=option read
# Look at the 3rd byte for WRPn
# https://github.com/stlink-org/stlink/blob/c4762e69a7a497568aa6f76cf1fab637e953e61b/inc/stm32flash.h#L263
recipy = "..\\data_rlnc\\rlnc_fixed4_50f_10b_fake_4gen_3red.bin"

start_address = "0x08060000"
print(f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe write {recipy} {start_address}")
subprocess.run(
    f".\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe write {recipy} {start_address}", shell=True, check=True)
