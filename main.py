import sys

def jopa(s: str):
  print("jopa", s)

# for _ in range(int(sys.stdin.readline())):
# 	s = [int(c) for c in sys.stdin.readline().strip()]
# 	n = len(s)
# 	m = int(sys.stdin.readline())
# 	l = sys.stdin.readline()
# 	r = sys.stdin.readline()
# 	mx = 0
# 	for i in range(m):
# 		li = int(l[i])
# 		ri = int(r[i])
# 		nmx = mx
# 		for c in range(li, ri + 1):
# 			cur = mx
# 			while cur < n and s[cur] != c:
# 				cur += 1
# 			nmx = max(nmx, cur)
# 		mx = nmx + 1
# 	print("YES" if mx > n else "NO")