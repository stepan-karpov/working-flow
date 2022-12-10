from math import gcd

n = int(input())
ans = 0

for i in range(1, n + 1):
  for j in range(1, n + 1):
    if (gcd(i, j) == 1):
      ans += 1

print(ans)