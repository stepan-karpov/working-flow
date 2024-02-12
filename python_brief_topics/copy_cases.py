import copy

a = [1, [2]]
b = a

b.append(23)
b[1].append(243)

print(a)

c = [1, [2]]
d = copy.copy(c)

d.append(4)
d[1].append(5)

print(c)

e = [1, [2]]
f = copy.deepcopy(e)

f.append(3)
f[1].append(4)

print(f)