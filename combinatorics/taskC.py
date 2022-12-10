from math import sqrt

def F(n):
  return ((((1 + sqrt(5)) / 2) ** (n) - ((1 - sqrt(5)) / 2) ** (n))) // sqrt(5);

def F_1(n):
  ans = F(n + 2) - 1
  return ans

def F_2(n):
  ans = F(n) * F(n + 1)
  return ans

def F_3(n):
  ans = (F(3 * (n - 1) + 5) + 6 * F(n - 1) * ((-1) ** (n - 1)) + 5) / 10
  n -= 1
  ans = (F(n + 1) * F(n + 2) * F(n + 2) + ((-1) ** n) * F(n) + 1) / 2 * F(n)
  return ans

def cnt_ans(n):
  ans = (F(3 * n + 2) - 1) // 2 - F(n + 1) ** 3 - F(n) ** 3 + 1

  return int(ans)

a = []
for i in range(0, 15):
  if (len(a) == 0):
    a.append(0)
  else:
    a.append(int(a[len(a) - 1] + F(i) * F(i) * F(i)))

b = []
for i in range(0, 15):
  if (len(b) == 0):
    b.append(0)
  else:
    b.append(cnt_ans(i))

print(a)
print(b)