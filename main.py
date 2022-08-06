from random import shuffle
a = []

for i in range(0, 16):
    a.append(0)
for i in range(0, 8):
    a.append(1)
for i in range(0, 4):
    a.append(2)
for i in range(0, 2):
    a.append(3)
for i in range(0, 1):
    a.append(4)
for i in range(0, 1):
    a.append(5)


shuffle(a)

a = [0, 3, 2, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 5, 0, 1, 0, 1, 0, 1, 3, 0, 2, 0, 1, 1, 4, 0, 0, 2, 1, 1]

x1 = int(input())
x2 = int(input())

x1 -= 1
x2 -= 1

if (a[x1] == a[x2]):
    print(0)
elif (a[x1] > a[x2]):
    print(1)
else:
    print(2)