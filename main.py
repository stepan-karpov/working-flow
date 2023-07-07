def BinPow(k, x):
  if (x == 0):
    return 1;
  if (x % 2 == 0):
    t = BinPow(k, x // 2);
    return t * t;
  else:
    return k * BinPow(k, x - 1);


def solve(n):

  if (n == 1):
    return False

  for k in range(2, 30):
    cur_power = 0;
    cur = 0
 
    while (cur < n):
      cur += BinPow(k, cur_power);
      cur_power += 1
    
    if (n == cur and cur_power != 2):
      return True;

  for x in range(3, 15):
    l = 2
    r = int(pow(10, 18 / x + 1))
    while (r - l > 1):
      m = (l + r) // 2
      value = (BinPow(m, x) - 1) // (m - 1)
      if (value > n):
        r = m
      else:
        l = m
    


    value1 = (BinPow(l, x) - 1) // (l - 1);
    value2 = (BinPow(l + 1, x) - 1) // (l);
    if (value1 == n or value2 == n):
      return True

  return False

t = int(input())

for i in range(0, t):
  n = int(input())
  if (solve(n)):
    print("YES")
  else:
    print("NO")

# for i in range(0, 10000):
#   # n = int(input())
#   if (solve(int(1e18) + i)):
#     # print("YES")
#     pass
#   else:
#     pass
#     # print("NO")