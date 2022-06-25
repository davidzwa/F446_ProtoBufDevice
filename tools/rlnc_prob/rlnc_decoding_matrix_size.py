import numpy as np
import matplotlib.pyplot as plt
from math import ceil, floor


U_F = 60000
F = range(20, 76, 1)
G = range(20, 41, 5)


def matrix_size(g, f):   
    return g * (g+f)


# Unit test
# F = 30
# G = 20
# print(matrix_size(G, F))
# print(20 * (20 + 30))
# Should show 1000 bytes


for g in G:
    S_Ds = np.array([])
    S_Ds2 = np.array([])
    for f in F:
        size = matrix_size(g, f)
        S_Ds = np.append(S_Ds, size)
        
        nf = ceil(U_F / f)
        ng = ceil(nf / g)
        S_D2 = ceil(nf/ng) * (ceil(nf/ng) + ceil(U_F/nf))
        print(g, f, nf, ng, f*g*ng, U_F, size, S_D2)
    

    plt.plot(F, S_Ds, label=f"Generation size (G={g})")

plt.grid(True)
plt.scatter(x=30, y=matrix_size(20, 30), label='Example calculation')
plt.legend()
plt.title("Decoding matrix size vs fragment size $U_{firmware}$ 60kB")
plt.xlabel("Fragment size [bytes]")
plt.ylabel("Decoding matrix size [bytes]")
plt.savefig('28_matrix_size.pdf')
