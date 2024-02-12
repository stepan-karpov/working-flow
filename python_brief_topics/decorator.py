import functools

def my_decorator(function):
  @functools.wraps(function)
  def inner(*args, **kwargs):
    print(f"Before {function.__name__}")
    result = function(*args, **kwargs)
    print(f"After {function.__name__}")
    return result
  return inner

@my_decorator
def funct(a: int, b: int, c: int = 1):
  print(f'My name is: {funct.__name__}')
  return a + b + c

funct(34, c=12, b=43)
