def function(a: int = 1, *args, **kwargs):
  print(a)
  print(args)
  print(kwargs)

function(34, 54, "s", 1.0, b=45, dog='haha')