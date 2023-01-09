ans = [0]

for i in range(0, 105):
  ans.append(1)

for i in range(0, 106):
  if (i % 3 == 0):
    ans[i] = -ans[i];
for i in range(0, 106):
  if (i % 5 == 0):
    ans[i] = -ans[i];
for i in range(0, 106):
  if (i % 7 == 0):
    ans[i] = -ans[i];

print(sum(ans))