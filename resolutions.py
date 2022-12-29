# x1 x2 x3 x4 x5 x6
sequence = [
  # [[1, 2, 0, 0, 0, 0, 0, 0, 0], 0, 0, 0],
  # [[1, 1, 0, 0, 0, 0, 0, 0, 0], 0, 0, 0],
  # [[2, 0, 0, 0, 0, 0, 0, 0, 0], 0, 0, 0],
]

# эта функция строит КНФ
# исходя из условий, заданных в задаче
def build_sequence():
  global sequence
  a = {
    #   0  1  2  3  4  5  6  7  8  9
    0: [1, 1, 0, 0, 0, 1, 1, 0, 0, 0],
    1: [0, 1, 0, 1, 0, 0, 0, 1, 0, 1],
    2: [0, 0, 0, 1, 1, 0, 1, 0, 1, 0],
    3: [0, 0, 1, 0, 1, 1, 0, 0, 0, 1],
    4: [1, 0, 1, 0, 0, 0, 0, 1, 0, 1],
  }
  edges = {
    0: [0, 1, 5, 6],
    1: [1, 3, 7, 9],
    2: [3, 4, 6, 8],
    3: [2, 4, 5, 9],
    4: [0, 2, 7, 8],
  }
  p = [
    [[]],
    [[0], [1], [2], [3]],
    [[0, 1], [0, 2], [0, 3], [1, 2], [1, 3], [2, 3]],
    [[0, 1, 2], [0, 1, 3], [0, 2, 3], [1, 2, 3]],
    [[0, 1, 2, 3, 4]],
  ]
  for i in range(0, 5):
    temp = [0, 2, 4]
    if (i != 0):
      temp = [1, 3]
    for t in temp:
      for k in p[t]:
        cur_add = []
        for jk in range(0, len(a[i])):
          cur_add.append(a[i][jk])
        for l in k:
          cur_add[l] = 2
        if ([cur_add, 0, 0, 0] not in sequence):
          sequence.append([cur_add, 0, 0, 0])


# посчитать резольвенту из наборов sequence1 и sequence2
def calc_resolvent(sequence1, sequence2, cur):
  global n
  answer = []
  for i in range(0, n):
    if (i == cur):
      answer.append(0)
      continue
    v1 = sequence1[i]
    v2 = sequence2[i]
    if (i != cur and (v1 == 1 and v2 == 2) or (v1 == 2 and v2 == 1)):
      return [-1]
    if (v1 == 0 and v2 == 0):
      answer.append(0)
    if (v1 == 0 and v2 == 1):
      answer.append(1)
    if (v1 == 0 and v2 == 2):
      answer.append(2)
    
    if (v1 == 1 and v2 == 0):
      answer.append(1)
    if (v1 == 1 and v2 == 1):
      answer.append(1)
    
    if (v1 == 2 and v2 == 0):
      answer.append(2)
    if (v1 == 2 and v2 == 2):
      answer.append(2)
    
  return answer

# эта функция выводит все возможные
# формулы из уже существующих с помощью метода
# резолюций по x_[current_variable]
def resolve(current_variable):
  global sequence
  global n
  global found
  to_find = []
  for i in range(n):
    to_find.append(0)
  for i in range(0, len(sequence)):
    for j in range(i + 1, len(sequence)):
      if (found):
        return
      v1 = sequence[i][0][current_variable]
      v2 = sequence[j][0][current_variable]
      if ((v1 == 1 and v2 == 2) or (v1 == 2 and v2 == 1)):
        temp = calc_resolvent(sequence[i][0], sequence[j][0], current_variable)
        if (temp != [-1]):
          if (temp == to_find):
            found = True
          used = False
          for k in range(0, len(sequence)):
            if (sequence[k][0] == temp):
              used = True
              break
          cur_ent = 0
          for var in temp:
            if (var != 0):
              cur_ent += 1
          if (not used and cur_ent < 10):
            sequence.append([temp, i, j, 0])

# красивый вывод
def beautify(sequence):
  answer = ""
  prev = False
  for i in range(0, len(sequence)):
    if (sequence[i] == 0):
      continue
    if (sequence[i] == 1):
      if (prev):
        answer += " or"
      answer += " (not x" + str(i) + ")"
      prev = True
    if (sequence[i] == 2):
      if (prev):
        answer += " or"
      answer += " x" + str(i)
      prev = True

  if (answer == ""):
    return " !"
  return answer


def GenerateFormula(cur_formula):
  p1 = sequence[cur_formula][1]
  p2 = sequence[cur_formula][2]
  if (sequence[cur_formula][3] == 1):
    return
  if (p1 + p2 == 0):
    print(cur_formula, ":", end="")
    print(beautify(sequence[cur_formula][0]))
    sequence[cur_formula][3] = 1
    return
  
  GenerateFormula(p1)
  GenerateFormula(p2)
  print(cur_formula, ":", p1, "+", p2, "=>", end="")
  print(beautify(sequence[cur_formula][0]))

  sequence[cur_formula][3] = 1

build_sequence()

found = False
n = len(sequence[0][0]) # number of variables

for i in range(0, len(sequence)):
  cur_d = beautify(sequence[i][0])
  cur_d = cur_d.strip()
  print(cur_d)

print()
print()

while (not found):
  for i in range(0, n):
    resolve(i)
    print(len(sequence))

GenerateFormula(len(sequence) - 1)