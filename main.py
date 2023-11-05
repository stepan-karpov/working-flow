def BinPow(a, x, mod):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    temp = BinPow(a, int(x / 2), mod)
    return (temp * temp) % mod
  return (a * BinPow(a, x - 1, mod)) % mod

mod = 1000000007
a, b, c, d = map(int, input().split())

t1 = ((a * d + b * c) % mod + mod * 10) % mod
t2 = ((b * d) % mod + 10 * mod) % mod
t3 = BinPow(t2, mod - 2, mod)

print((t1 * t3) % mod)

