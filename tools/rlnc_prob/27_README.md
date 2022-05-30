Lessons learnt from x coefficient:
1) Giving it a logarithmic x-axis helps to focus more on the lower values of x
1b) The lower x is (log-space), the heavier impact burst has - it models heavy outages better
1c) PER can easily become almost double pi_B if x is below 10E-2

2) Redundancy Used is vague because it indicates the redundancy was enough
2b) Combine with temporal PER and success draws a better picture

3) The sim is super slow due to constantly recalculating the same values
3b) Making a LUT for the internal decoding success rates is better and if value is > G+2 we can estimate 100% success
