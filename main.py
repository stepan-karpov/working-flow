import math
n = 1000

p = 1

for k in range(1, n):
  p *= (k / (k + n))


ans = pow(p, math.exp(2024 / n) - 1)

print(ans)