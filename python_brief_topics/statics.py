#     static variables

class MyClass:
  stat_value: int  = 234

  def __init__(self):
    self.value = 1
  

a = MyClass()
b = MyClass()

print(a.stat_value, b.stat_value)

MyClass.stat_value = 235

print(a.stat_value, b.stat_value)
