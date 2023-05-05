def C(n, k):
  fact = 1
  for i in range(1, n + 1):
    fact *= i
  for i in range(1, n - k + 1):
    fact //= i
  for i in range(1, k + 1):
    fact //= i

  return fact

def Cat(n):
  return C(2 * n, n) // (n + 1)

n = int(input())

print(Cat(n + 1))