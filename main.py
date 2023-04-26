import traceback
import sys
import os

a, b, c = map(int, input().split())

a *= 10 ** (c)

a //= b

s = str(round((a / (10 ** c)), c))
ind = -1
print(s)
for i in range(len(s)):
    if (s[i] == '.'):
        ind = i
        break

sz = 0
for i in range(ind + 1, len(s)):
    sz+=1

print(s, end='')
for i in range(c - sz):
    print(0, end='')
    