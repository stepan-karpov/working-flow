t = int(input())

for test in range(0, t):
    s = int(input())
    curV = ""

    curVal = 9

    while (s > curVal):
        curV = str(curVal) + curV
        s -= curVal
        curVal -= 1

    if (s != 0):
        curV = str(s) + curV

    print(curV)