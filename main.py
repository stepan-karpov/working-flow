def BinPow(a, x, mod):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    temp = BinPow(a, int(x / 2), mod)
    return (temp * temp) % mod
  return (a * BinPow(a, x - 1, mod)) % mod

mod = 7340033


kMod = 7340033
kRoot = 5
kRoot1 = 4404020
kRootpw = 1 << 20

kMod = 7
kRoot = 3
kRoot1 = 5
kRootpw = 6

print(BinPow(kRoot, kRootpw, kMod))
print((kRoot * kRoot1) % kMod)