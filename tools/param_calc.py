import numpy as np
import math

from rlnc_prob.shared import calc_lora_tpacket

# Phy config
SF: int = 7
CR: int = 1
BW: int = 500 * math.pow(10, 3)
PreSymb: int = 8
PayloadMax: int = 22

# Fixed-point optimization
optimization_iterations_max: int = 96

# Sending without limits
frame_period_tx = 50
gen_period = 1000

# Sending with limits Class B
class_b_periodicity = 2**7
class_b_duty_cycle = 0.1

# RLNC parameters
frame_size_min: int = 10
firmware_size = 200000
generation_size: int = 20
generation_redundancy: float = 3

# Target payload
firmware_size_kb = firmware_size / 1000
frame_count = firmware_size / frame_size_min
generation_redundancy_perc = generation_redundancy * 100
generation_total_size: int = math.ceil(
    generation_size * (1+generation_redundancy))
generation_count = math.ceil(firmware_size / (generation_size * firmware_size_kb))

beacon_occupation: float = 128.0 * class_b_duty_cycle
# Duration of ping slot
pingslot_duration: float = beacon_occupation / class_b_periodicity
pingslot_duration_ms: float = pingslot_duration * 1000

print("\n-- RLNC")
print(f"Firmware size {firmware_size_kb}kB")
print(f"Frame    size {frame_size_min}b")
print(f"Frame   count {frame_count:.0f} (min size {frame_size_min}b)")
print(
    f"Generation size {generation_size} (with {generation_redundancy_perc}% redundancy: {generation_total_size})")
fragment_total = generation_total_size * generation_count
fragment_min = generation_size * generation_count
print(
    f"Generation count {generation_count} ({generation_size} frames each)")
print(
    f"Fragment total {fragment_total} > {fragment_min} optimum")


frame_meta_size = 4
proto_extra = 4

def calc_optimal_frame_size(min_frag: int):
    current_frag = min_frag
    last_frag = None
    last_duration = None
    current_duration = None
    
    iterations = 0
    while (iterations < optimization_iterations_max):
        current_duration = calc_lora_tpacket(current_frag, SF, BW, CR, PreSymb)

        diff = current_duration - pingslot_duration
        if (diff > 0):
            removed =math.floor((current_duration+pingslot_duration)/(pingslot_duration))
            # print("decrease", removed)
            current_frag -= removed
        else:
            added = math.floor((current_duration+pingslot_duration)/current_duration)
            # print("increase", added)
            current_frag += added
        
        if current_frag > 225:
            current_frag = 225
            current_duration = calc_lora_tpacket(current_frag, SF, BW, CR, PreSymb)
            return current_frag, current_duration

        # print(f"frag {current_frag:.4f} {current_duration:.4f} {pingslot_duration:.4f}")
        last_duration = current_duration
        last_frag = current_frag
        iterations +=1

    if (current_duration > pingslot_duration):
        return last_frag, last_duration
    else:
        return current_frag, current_duration

max_frame_size, duration = calc_optimal_frame_size(frame_size_min)    
print(f"-> done duration {duration:.4f}")

fragment_size = max_frame_size - frame_meta_size - proto_extra
t_packet, t_payload, payload_symb, payload_symb_nb = calc_lora_tpacket(
    fragment_size, SF, BW, CR, PreSymb)

print(f"Time {t_packet} slot {pingslot_duration} frame_max {max_frame_size} fragment {fragment_size}")

# Calculate impact of parameter choice
# generation_sizes: np.ndarray = np.array(range(15, 50, 3))
# generation_sizes_2 = np.power(generation_sizes, 2)
# generation_sizes_f = np.multiply(generation_sizes, frame_size)

# 32 bits values in std_vector (so with linear overhead)
# matrix_size_range = generation_sizes_2 + generation_sizes_f

# for i in range(0, len(generation_sizes)):
#     print(generation_sizes[i], matrix_size_range[i])

print("\n-- Physical")
aug_matrix_size = generation_size * (generation_size + frame_size_min)
aug_matrix_real_size = aug_matrix_size * 4
print(
    f"Decoding matrix size {aug_matrix_size}, {aug_matrix_real_size}b memory")
print("Frame size", max_frame_size)
print("Payload size", fragment_size)
t_packet_ms = t_packet * 1000
t_payload_ms = t_payload * 1000
overhead = 100 * (1.0 - payload_symb_nb / (fragment_size + payload_symb_nb))
print(f"LoRa bytes {payload_symb_nb} (overhead {overhead:.1f}%)")
print(f"LoRa ToA {t_packet_ms:.2f}ms, payload ToA {t_payload_ms:.2f}ms")

print("\n-- Time")
print(f"Beacon occupation {beacon_occupation}s")
print(
    f"Class B ping slot duration {class_b_periodicity} slots of {pingslot_duration_ms}ms each")
correction = 1
if (pingslot_duration < t_packet):
    correction = math.floor(t_packet/pingslot_duration)

beacon_periods = fragment_total / class_b_periodicity
real_duration = beacon_periods * 128
real_duration_min = real_duration / 60
optimality = t_packet / pingslot_duration
optimality_perc = optimality * 100
limitless_duration = (frame_period_tx * fragment_total +
                      generation_count * gen_period) / 1000
print(f"Duration high-speed experiment {limitless_duration}s")
optimal_real_duration_min = min(real_duration_min * optimality, fragment_total / math.floor(beacon_occupation / t_packet) * 128)
print(f"Class B duration {real_duration_min:.1f}min ({optimality_perc:.1f}% eff, opt. {optimal_real_duration_min:.1f}min at {t_packet_ms:.2f}ms out of {pingslot_duration_ms}ms)")
