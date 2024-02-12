class Animal:
  age = 0
  hunger_percentage = 100

  def __init__(self, age: int):
    self.age = age
    print("main constructor")

  def eat(self, food: int):
    self.hunger_percentage -= food
  
  def print_info(self):
    print(f'Age: {self.age}, hunger_percentage: {self.hunger_percentage}')

  def voice(self):
    print("Voice")

class Dog(Animal):
  def __init__(self, age: int):
    super().__init__(age)
    print("heir's constructor")

  def voice(self):
    print("Wuf!") 

Girrafe = Animal(21)
Girrafe.print_info()
Girrafe.eat(15)
Girrafe.print_info()

print("----------")

Dog = Dog(12)
Dog.voice()
Dog.print_info()

