import sys
import functools


def takes(*dec_args):
  argument_types = list(dec_args)

  def wraps(func):

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
      arguments_list = list(args)
      nonlocal argument_types
      size = min(len(arguments_list), len(argument_types))
      for i in range(size):
         if (type(arguments_list[i]) != argument_types[i]):
           raise TypeError
      func(*args, **kwargs)
    
    return wrapper
  
  return wraps


@takes(int, str)
def f(a, b):
    print(a, b)

try:
    f(1, 2)
except Exception as e:
    print(type(e).__name__)

