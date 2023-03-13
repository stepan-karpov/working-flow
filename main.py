from math import sqrt

for i in range(1, 100):
    x = sqrt(i) + ((-1) ** i) / sqrt(i) / 2
    print(x)