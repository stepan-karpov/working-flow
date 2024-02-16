# def my_generator():
#   for i in range(0, 15):
#     if (i % 4 == 0):
#       yield i

# a = [x ** 2 for x in range(5)]
# print(a)

# a = [x for x in my_generator()]
# print(a)

# a = {x ** 2 for x in range(5)}
# print(a)


# a = {x: x ** 2 for x in range(5)}
# print(a)

gen = (x for x in range(0, 10) if x % 2 == 0)

print(next(gen))

print(list(gen))

a = {x ** 2 for x in range(-4, 5)}
print(a)