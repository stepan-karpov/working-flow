def append(my_list):
  my_list = [0, 0]
  my_list[0] = 1
  return 2
my_list = (0, 1)
my_list[0] = append(my_list)
print(my_list)