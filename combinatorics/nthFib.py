from math import sqrt

n = 4


f1_n = ((((1 + sqrt(5)) / 2) ** (n + 2) - ((1 - sqrt(5)) / 2) ** (n + 2))) / sqrt(5)
f2_n = ((3 + 2 * sqrt(3)) / 6) * ((1 + sqrt(3)) ** n) + ((3 - 2 * sqrt(3)) / 6) * ((1 - sqrt(3)) ** n)

print(f1_n)
print(f2_n)