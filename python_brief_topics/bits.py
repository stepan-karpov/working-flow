a = 12

print(bin(a))

for i in range(10, -1, -1):
  print(a >> i & 1, end='')

print()
print()
print()

for i in range(10):
  print(a >> i & 1, end='')

# 001 >> 1 -> 00