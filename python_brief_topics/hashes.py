import typing

class MyClass:
  def __init__(self, id: int, name: str):
    self.id = id
    self.name = name
  
  def __hash__(self):
    return self.id * 2


test = MyClass(1, 'Hi!')

di = {test: 1}

print(hash(test))
print(isinstance([], typing.Hashable))
print(isinstance(test, typing.Hashable))