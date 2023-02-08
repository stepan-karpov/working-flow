def binPow(a, x):
  if (x == 0):
    return 1
  if (x % 2 == 0):
    t = binPow(a, x // 2)
    return t * t
  return binPow(a, x - 1) * a

k = binPow(9, 9)
# print(k)
# print(binPow(k, 9))
print(binPow(9, k))