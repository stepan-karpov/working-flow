ans = []
n = 21

def backtrack(a):
  if (sum(a) > 21):
    return
  
  if (sum(a) == 21):
    ans.append(a)
  
  for i in [1, 4, 6, 9]:
    a.append(i)
    backtrack(a)
    a.pop()

backtrack([])
print(len(ans))