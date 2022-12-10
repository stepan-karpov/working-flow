from math import sqrt

ans = 0
ans2 = 0
MOD = int(1e9) + 7

n = int(input())

def BinPow(a, x):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    t = BinPow(a, x // 2)
    return (t * t) % MOD
  return (a * BinPow(a, x - 1)) % MOD

for m in range(1, n + 1):
  temp = BinPow(2, BinPow(2, m))
  temp -= BinPow(2, BinPow(2, m - 1))
  temp %= MOD
  temp *= BinPow(BinPow(2, m), MOD - 2)
  ans += temp
  ans2 += temp
  ans %= MOD

ans += 2
ans2 += 2

print(ans)
print(ans2 % MOD)