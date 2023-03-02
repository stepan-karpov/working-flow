f = ""

for i in range(1, 1000):
  if (i % 3 == 0):
    f += "F"
  if (i % 5 == 0):
    f += "B"

t = int(input())

for i in range(0, t):
  n = int(input())
  s = input()

  if (f.count(s) == 0):
    print("NO")
  else:
    print("YES")