def FindHeight(osn, s):
  return (s + osn - 1) // osn

def TernarySearch(s):
  l = 0
  r = 2 * 1e18 * 2

  while (r - l > 2):
    m1 = l + (r - l) // 3
    m2 = r - (r - l) // 3

    h1 = FindHeight(m1, s)
    h2 = FindHeight(m2, s)

    if (m1 + h1 < m2 + h2):
      r = m2
    else:
      l = m1

  best_value = 1e18 * 4
  ans = l

  for i in range(-10, 11):
    if (l + i <= 0):
      continue

    cur_value = l + i + FindHeight(l + i, s)
    if (cur_value < best_value):
      ans = l + i
      best_value = cur_value

  return ans


s = int(input())
if (s == 0):
  print("0")
else:
  osn = TernarySearch(s)
  print(int(osn + FindHeight(osn, s)))
