def my_generator():
  for i in range(0, 15):
    if (i % 4 == 0):
      yield i

a = [x ** 2 for x in range(5)]
print(a)

a = [x for x in my_generator()]
print(a)

a = {x ** 2 for x in range(5)}
print(a)


a = {x: x ** 2 for x in range(5)}
print(a)