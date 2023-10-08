def GetBit(x, numb):
  return bool((x >> numb) & 1);

def SetBit(x, numb, v):
  if (v == 1):
    x |= (1 << numb)
  else:
    if (GetBit(x, numb) == 1):
      x ^= (1 << numb)
  return x

def BinPow(a, x):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    res = BinPow(a, x // 2)
    return res * res
  return a * BinPow(a, x - 1)

def Output(exp, dv, is_neg):
  if (exp == 0):
    print(0)
    return
  
  if (is_neg):
    print("-", end='')

  if (dv == 0):
    print(exp)
  elif (dv < 0):
    print(str(exp) + "/2**" + str(abs(dv)))
  else:
    print(str(exp) + "*2**" + str(abs(dv)))


k = int(input())
d = int(input())

m = d
p = 0

for i in range(k, 64):
  m = SetBit(m, i, 0)

for i in range(k, 63):
  p = SetBit(p, i - k, GetBit(d, i))

max_v = (1 << (63 - k)) - 1;

if (p == max_v):
  print("NaN")
else:
  value = 0
  if (p > 0):
    p1 = p + 1 - BinPow(2, 62 - k) - k
    exp = BinPow(2, k) + m
    while (exp > 0 and exp % 2 == 0):
      exp = exp // 2
      p1 += 1
    
    Output(exp, p1, GetBit(d, 63) == 1)
  else:
    exp = m
    p = 1 - BinPow(2, 62 - k) - k
    while (exp > 0 and exp % 2 == 0):
      exp = exp // 2
      p += 1

    Output(exp, p, GetBit(d, 63) == 1)
    # value = BinPow(2, 1 - BinPow(2, 62 - k)) * m / BinPow(2, k)
#   print(value)