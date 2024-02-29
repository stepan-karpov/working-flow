def foo(tmp=None):
  if tmp is None:
    tmp = []
  tmp.append(1)
  return tmp

def bar(tmp=()):
  tmp += (1,)
  return tmp

print(bar())
print(bar())
print(bar())
print(bar())