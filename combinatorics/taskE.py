from math import sqrt

MOD = int(1e9) + 7

def Dividers(n):
  ans = [1]
  if (n != 1):
    ans.append(n)
  for i in range(2, int(sqrt(n)) + 1):
    if (n % i == 0):
      ans.append(i)
      if (i * i != n):
        ans.append(n // i)
  return ans

def Mobius(n):
  p = 0
  last = -1
  for i in range(2, int(sqrt(n)) + 1):
    while (n % i == 0):
      if (i == last):
        return 0
      last = i
      p += 1
      n //= i
  if (n != 1):
    p += 1

  return pow(-1, p)

def BinPow(a, x):
  if (x == 0):
    return 1
  if (x == 1):
    return a % MOD
  if (x % 2 == 0):
    t = BinPow(a, x // 2)
    return (t * t) % MOD

  return (a * BinPow(a, x - 1)) % MOD

def T(k, n):
  ans = 0
  t = Dividers(n)
  t.sort()
  for m in t:
    cur_period = 0
    for d in Dividers(m):
      cur_period += Mobius(d) * BinPow(k, m // d)
      cur_period = (cur_period + MOD) % MOD
    cur_period *= BinPow(m, MOD - 2)
    cur_period %= MOD
    ans += cur_period + MOD
    ans %= MOD

  return ans

def C(n, k):
  ans = 1
  for i in range(1, n + 1):
    ans *= i
  for i in range(1, k + 1):
    ans //= i
  for i in range(1, n - k + 1):
    ans //= i
  return ans

n, k = list(map(int, input().split()))

ans = 0
p = 1

for i in range(0, k + 1):
  ans += C(k, i) * T(k - i, n) * p
  ans = (ans + MOD) % MOD
  p *= -1

print(ans * C(10, k) % MOD)