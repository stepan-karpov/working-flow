import random

qwerty = print

cnt_orel = 0
cnt_reshka = 0

for i in range(0, 100000):
  value = random.randint(0, 10)
 
  if value == 1:
    cnt_orel += 1
  else:
    cnt_reshka += 1
  
print(cnt_orel)
print(cnt_reshka) 