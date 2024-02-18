class Node:
  def __init__(self, value):
    self.previous_node = None
    self.next_node = None
    self.value = value

class LinkedList:   
  __size: int 
  __head: Node

  def __init__(self):
    self.__size = 0
    self.__head = None

  def __insert__(self, node, value):
    """
    inserts 'value' after node
    or inserts 'value' in list if len(list) == 0

    node <-> new_node <-> next_node
    """
    if self.__size == 0:
      self.__head = Node(value)
      self.__size += 1
      return

    self.__size += 1
    new_node = Node(value)
    next_node = node.next_node

    node.next_node = new_node
    new_node.previous_node = node
    new_node.next_node = next_node

    if next_node is not None:
      next_node.previous_node = new_node

  def push_back(self, value):
    current_value = self.__head
    if (current_value is None):
      self.__insert__(None, value)
      return

    while current_value.next_node is not None:
      current_value = current_value.next_node
    
    self.__insert__(current_value, value)
  
  def pop_back(self):
    if (self.__head is None):
      return
    
    current_value = self.__head

    while current_value.next_node is not None:
      current_value = current_value.next_node
    
    current_value.previous_node.next_node = None
    current_value = None
    self.__size -= 1

  def __len__(self):
    return self.__size

  def __getitem__(self, index: int):
    current_value = self.__head
    for i in range(index):
      current_value = current_value.next_node

    return current_value.value

  def __repr__(self):
    answer = "["
    current_value = self.__head
    while current_value is not None:
      answer += repr(current_value.value) + ", "
      current_value = current_value.next_node
    return answer[:-2] + "]"
  
  def __iter__(self):
    class LinkedListIterator:
      def __init__(self, head):
          self.current_node = head

      def __iter__(self):
          return self

      def __next__(self):
        if self.current_node is None:
          raise StopIteration
        else:
          value = self.current_node.value
          self.current_node = self.current_node.next_node
          return value

    return LinkedListIterator(self.__head)
    

my_list = LinkedList()
my_list.push_back(12)
my_list.push_back(34)
my_list.push_back("sdf")
my_list.push_back(45)
my_list.pop_back()



print(my_list)
print(len(my_list))      
print(my_list[1])

it = iter(my_list)
for el in it:
  print(el, end=' ')