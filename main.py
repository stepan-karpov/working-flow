from random import randint

def get_degenerate_matrix():
  a = []
  for i in range(0, 3):
    temp = []
    for j in range(0, 3):
      temp.append(randint(0, 10))
    a.append(temp)
  if (find_determinant(a) == 0):
    return a
  return get_degenerate_matrix()

def find_determinant(a):
  p1 = a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1])
  p2 = a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
  p3 = a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0])
  return p1 - p2 + p3

def multiply_maxtrix(a, b):
  c = a
  for i in range(0, 3):
    for j in range(0, 3):
      c[i][j] = 0
      for k in range(0, 3):
        c[i][j] += a[i][k] * b[k][j]
  return c

while 1:
  a = get_degenerate_matrix()
  b = get_degenerate_matrix()
  c = multiply_maxtrix(a, b)
  if (find_determinant(c) != 0):
    print(a)
    print(b)
    print(c)
    break