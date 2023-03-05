def calculate(list_a, value_b):
    list_a.sort()
    value_b *= len(list_a)

a = [3, 1, 4, 1, 5]
b = 3

calculate(a, b)

print(a, b)
