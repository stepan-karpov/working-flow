from math import sqrt

ans = 0
MOD = int(1e9) + 7

def Mebius(n):
  p = 0
  last = -1
  for i in range(2, int(sqrt(n)) + 2):
    while(n % i == 0):
      if (last == i):
        return 0
      last = i
      p += 1
      n //= i
  if (n != 1):
    p += 1
  return int(pow(-1, p))

def Dividers(n):
  ans = []
  for i in range(1, int(sqrt(n)) + 1):
    if (n % i == 0):
      ans.append(i)
      if (i * i != n):
        ans.append(n // i)
  return ans

def BinPow(a, x):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    t = BinPow(a, x // 2)
    return (t * t) % MOD
  return (a * BinPow(a, x - 1)) % MOD


def CountPeriodic(k, period):
  ans = 0
  for d in Dividers(period):
    ans += Mebius(d) * BinPow(k, period // d)
    ans %= MOD
  
  ans *= BinPow(period, MOD - 2)
  ans %= MOD
  return ans


n, k = list(map(int, input().split()))

for period in Dividers(n):
  ans += CountPeriodic(k, period)
  ans = (ans + MOD) % MOD

print(ans)