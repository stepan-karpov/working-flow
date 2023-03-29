r = open("input.txt", mode='r')

ans = []

for line in r.readlines():
  words = line[30:].split()
  for word in words:
    c = word.strip("\n")
    if (c.lower() != c):
      continue
    if (word[0] == "."):
      continue
    if (word[-1] == "."):
      c = word[:-1]
    if (c.endswith(".hlm") or c.endswith(".brhl")):
      ans.append(c)

o = open("output.txt", mode='a')

for el in ans:
  o.write(el + "\n")

r.close()