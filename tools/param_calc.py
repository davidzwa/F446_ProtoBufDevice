import numpy as np
import math

firmware_size = 1000
firmware_size_kb = firmware_size / 1000

frame_size: int = 10
generation_size: int = 26
generation_redundancy_perc: float = 0.3
generation_total_size: int = math.ceil(
    generation_size * (1+generation_redundancy_perc))

frame_period_tx = 50
gen_period = 1000
class_b_periodicity = 128
class_b_duty_cycle = 0.1

SF: int = 7
CR: int = 1
BW: int = 500 * math.pow(10, 3)
PreSymb: int = 8
PayloadMax: int = 22

frame_meta_size = 4
proto_extra = 4


def calcPacketSize(pSize: int, implHdr: bool = False):
    tSymb = math.pow(2, SF) / BW
    tPreamble = (PreSymb + 4.25) * tSymb

    numerator = 8 * pSize - 4 * SF + 28 + 16 - 20 * implHdr
    denominator = 4 * SF  # Skipped low DR (=12) for now
    payload_symb = math.ceil(numerator / denominator) * (CR + 4)
    payload_symb_nb = 8 + max(payload_symb, 0)

    t_payload = payload_symb_nb * tSymb
    t_packet = tPreamble + t_payload
    return t_packet, t_payload, payload_symb, payload_symb_nb


# Calculate impact of parameter choice
generation_sizes: np.ndarray = np.array(range(15, 50, 3))
generation_sizes_2 = np.power(generation_sizes, 2)
generation_sizes_f = np.multiply(generation_sizes, frame_size)

# 32 bits values in std_vector (so with linear overhead)
matrix_size_range = generation_sizes_2 + generation_sizes_f

for i in range(0, len(generation_sizes)):
    print(generation_sizes[i], matrix_size_range[i])

print("--")

generation_count = math.ceil(firmware_size / generation_size)
fragment_total = generation_total_size * generation_count
fragment_min = generation_size * generation_count
print(f"Firmware size {firmware_size_kb}kB")
print(
    f"Generation count {generation_count} ({generation_size} core frames per gen)")
print(
    f"Fragment total {fragment_total} > {fragment_min} optimum ({generation_total_size} per gen)")

print("-- Physical")
aug_matrix_size = generation_size * (generation_size + frame_size)
aug_matrix_real_size = aug_matrix_size * 4
fragment_size = frame_size + frame_meta_size + proto_extra
print(
    f"Decoding matrix size {aug_matrix_size}, {aug_matrix_real_size}b memory")
print("Frame size", frame_size)
print("Fragment size", fragment_size)
t_packet, t_payload, payload_symb, payload_symb_nb = calcPacketSize(
    fragment_size)
t_packet_ms = t_packet * 1000
t_payload_ms = t_payload * 1000
overhead = 100 * (1.0 - payload_symb_nb / (fragment_size + payload_symb_nb))
print(f"LoRa bytes {payload_symb_nb} (overhead {overhead:.1f}%)")
print(f"LoRa ToA {t_packet_ms:.2f}ms, payload ToA {t_payload_ms:.2f}ms")

print("-- Time")
total_duration = (frame_period_tx * fragment_total +
                  generation_count * gen_period) / 1000
print(f"Duration experiment {total_duration}s")
beacon_occupation: float = 128.0 * class_b_duty_cycle
# Duration of ping slot
pingslot_duration: float = beacon_occupation / class_b_periodicity
pingslot_duration_ms: float = pingslot_duration * 1000

print(f"Beacon occupation {beacon_occupation}s")
print(
    f"Class B ping slot duration ({class_b_periodicity} slots) {pingslot_duration_ms}ms")
correction = 1
if (pingslot_duration < t_packet): 
    correction = math.floor(t_packet/pingslot_duration)
real_duration = 128 * correction * fragment_total * t_packet
real_duration_min = real_duration / 60
print(f"Class B duration {real_duration_min:.1f}min")
