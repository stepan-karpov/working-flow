a, b, k = list(map(int, input().split()))

dec = a // b

f = a % b

if (f == 0):
  print(str(dec) + "." + "0" * k)
else:

  while (len(str(f // b)) != k + 1):
    f *= 10

  s = f // b
  if (s % 10 >= 5):
    s += 10

  print(str(dec) + "." + str(s // 10))