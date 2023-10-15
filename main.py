def fact(n):
  res = 1
  for i in range(1, n + 1):
    res *= i
  return res

def C(n, k):
  return fact(n) // fact(n - k) // fact(k)

s = 0

for i in range(0, 8):
  s += C(7, i) * pow(0.6, i) * pow(0.4, 7 - i)
  print(i, ' ', s)