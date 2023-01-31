t = int(input())

ALPH1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
ALPH2 = "abcdefghijklmnopqrstuvwxyz"

def dec_to_hex(x):
  d = "0123456789ABCDEFGHIJKL"
  ans = []
  while(x > 0):
    ans = [d[x % 16]] + ans
    x //= 16

  return ans

for i in range(0, t):
  inp = input().split(",")
  un = len(set(inp[0] + inp[1] + inp[2]))
  

  day = int(inp[3])
  month = int(inp[4])
  
  num = ALPH1.find(inp[0][0])
  if (num == -1):
    num = ALPH2.find(inp[0][0])
  num += 1
  
  s = un
  s += (day % 10 + day // 10 + month % 10 + month // 10) * 64
  s += num * 256

  ans = dec_to_hex(s)

  while (len(ans) < 3):
    ans = [0] + ans
  
  for i in range(len(ans) - 3, len(ans)):
    print(ans[i], end="")

  print()
