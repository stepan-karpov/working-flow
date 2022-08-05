import queue

def solve():
    x, k = list(map(int, input().split()))

    n = int(input())
    d = []
    if (n != 0):
        d = list(map(int, input().split()))

    d.sort()

    possible = {
        1: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        2: [0, 2, 4, 6, 8],
        3: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        4: [0, 2, 4, 6, 8],
        5: [0, 5],
        6: [0, 2, 4, 6, 8],
        7: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        8: [0, 2, 4, 6, 8],
        9: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
    }

    if (x % k == 0):
        return x

    ls = k % 10
    ok = False

    for i in d:
        if (i in possible[ls]):
            ok = True

    if (not ok):
        return -1

    ans = -1

    q = queue.Queue()
    q.put(x)

    ans = -1

    while (not q.empty()):
        x = q.get()

        if (x % k == 0):
            if (ans == -1):
                ans = x
            ans = min(ans, x)
            break

        for i in d:
            q.put(int(str(x) + str(i)))

    return ans

print(solve())