num = int(input())

found = 0
i = 0

while (True):
  i += 1
  if (str(i).count("3") == 3):
    found += 1
  if (found == num):
    print(i)
    break