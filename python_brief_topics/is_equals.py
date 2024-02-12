a = [1, 2, 3]
b = [1, 2, 3]

print(id(a))
print(id(b))
print(a is b, a == b)

a = 12
b = 12
print(id(a))
print(id(b))
print(a is b, a == b)