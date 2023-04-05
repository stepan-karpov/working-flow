from math import atan2, pi, sqrt
from math import acos

d, h, w, k = map(int, input().split())

if (h >= 2 * w):
  min_ans = atan2(w, d)
  if (4 * w * w + 4 * d * d <= k * k):
    print(min_ans / pi * 180)
  else:
    print("-1")
else:
  if (k * k - 4 * d * d >= w * w * 4):
    angle = acos(2 * d / k)
    print(angle / pi * 180)
  else:
    print("-1")
    