a = [1, 2, 3, 4, 5]

it = iter(a)

print(next(it))
print(next(it))

for el in it:
    print(el)
