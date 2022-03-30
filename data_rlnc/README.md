rlnc_50f_10b_fake_4gen_3red
Original flash

rlnc_fixed2_50f_10b_fake_4gen_3red
- Reversed the BitConverter output to counter endianness

rlnc_fixed2_50f_10b_fake_4gen_3red
- Fixed the generation redundancy to be included

rlnc_fixed3_50f_10b_fake_4gen_3red
- (REAPPLIED BLOB) Fixed the generation redundancy to be included

rlnc_fixed4_50f_10b_fake_4gen_3red.bin
- Corrected for final generation with probably less fragments

rlnc_fixed5_50f_10b_fake_4gen_3red.bin
- Simplified update header with next generation index

rlnc_fixed6_50f_10b_fake_4gen_3red.bin
- Updated Init packet with reception config

### STABLE OUTDATED (breaking change fragment header)
rlnc_fixed6b_50f_10b_fake_4gen_3red.bin
- Removed correlation code and device id from termination packet

### UNTESTED VERSIONS BELOW 

rlnc_fixed7_300f_20b_fake_10gen_3red.bin
- Incremented sequence number to 16-bits (Error: didnt invert)
- Massively increased the fragment count, the fragment size, the generation size up to 1kB of matrix RAM 

rlnc_fixed8_400f_22b_fake_13gen_3red.bin