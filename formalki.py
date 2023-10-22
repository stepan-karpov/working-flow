ans = []

def dfs(current_string, depth):
  if (current_string.count('S') == 0):
    ans.append(current_string)
  if (depth == 7):
    return

  for i, symb in enumerate(current_string):
    if (symb == 'S'):
      dfs(current_string[0:i] + 'ab' + current_string[i + 1:], depth + 1)
      dfs(current_string[0:i] + 'aSb' + current_string[i + 1:], depth + 1)
      dfs(current_string[0:i] + 'SS' + current_string[i + 1:], depth + 1)

dfs('S', 0)

ans = list(set(ans))
ans.sort()
for w in ans:
  print(w)