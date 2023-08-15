def check(s, t):
    if len(s) != len(t):
        return  'NO'
    dicts = {}
    dictt = {}
    for pair in zip(s, t):
        if dicts.setdefault(pair[0], pair[1]) != pair[1]:
            return 'NO'
        if dictt.setdefault(pair[1], pair[0]) != pair[0]:
            return 'NO'
    return 'YES'

t = int(input())

for i in range(t):
  s1 = input()
  s2 = input()
  print(check(s1, s2)) 