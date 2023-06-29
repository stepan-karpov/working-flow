import math

def isPrime(x):
  for i in range(2, int(math.sqrt(x)) + 1):
    if (x % i == 0):
      return False
  return True

for i in range(4, 100, 4):
  if (isPrime(i - 1)):
    print(i)


