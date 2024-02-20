def function(a: int = 1, *args, **kwargs):
  print(a)
  print(args)
  print(kwargs)

function(34, 54, "s", 1.0, b=45, dog='haha')

print(*[1, 4, 5, 6])
print(**{"s": 5, "a": 2, "b": 4, "c": 6, "d": 3, "e": 2})