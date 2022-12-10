values = []
LENGTH = 5
ALPH = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']
# ALPH = ['a', 'b', 'c', 'd']
K = 2

def shift(a):
  t = a[0]
  ans = ""
  for i in range(1, len(a)):
    ans += a[i]
  return ans + t

def backtrack(a):
  if (len(a) == LENGTH):
    if (len(set(a)) != K):
      return
    
    for i in range(0, len(a)):
      if (a in values):
        return
      a = shift(a)
    
    values.append(a)
    return
  
  for el in ALPH:
    backtrack(a + el)

backtrack("")
print(len(values))