import galois

GF = galois.GF(2**8)

# for x in range(1,256):
#     val = GF(1) / GF(x)
#     print(val)

print(hex(GF(0x82)/GF(0x4)))