# Import statistics Library
from statistics import median
import math

def median_index(l, r):
    n = r - l + 1
    n = (n + 1) // 2 - 1
    return n + l
 
# Function to calculate IQR
def IQR(a, n):
 
    a.sort()
 
    # Index of median of entire data
    mid_index = median(a, 0, n)
 
    # Median of first half
    Q1 = a[median(a, 0, mid_index)]
 
    # Median of second half
    Q3 = a[mid_index + median(a, mid_index + 1, n)]
 
    # IQR calculation
    return (Q3 - Q1)

def calc_median_index(array):
    new_array = array.copy()
    new_array.sort()
    length = len(new_array)
    n = (length + 1) / 2
    high = math.ceil(n) - 1
    low = math.floor(n) - 1
    return (high + low) / 2, high, low

array = [
    0.555555582,
    0.571428597,
    0.571428597,
    0.600000024,
    0.656666687,
    0.666666687,
    0.666666687,
    0.714285731,
    0.75,
    0.857142866
]

# THIS IS A TEST TO COMPARE WITH C# 

array.sort()
length = len(array)
is_odd = len(array) % 2 != 0
print(length, is_odd)
# n = (length + 1) / 2
# high = math.ceil(n)
# low = math.floor(n)
# median_val = None
# if is_odd:
#     print(high, low, array[high], array[low])
#     median_val = (array[high] + array[low]) / 2
# else:
#     median_val = array[high]

median_py = median_index(0, length)
print(median_py, (array[median_py] + array[median_py+1])/2)

print(is_odd)
index, high, low = calc_median_index(array)
print(index, high, low)

if is_odd:
    print(array[int(index)])
else:
    print((array[high] + array[low]) / 2)

# Calculate middle values
print(median(array))
