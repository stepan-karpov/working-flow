import itertools
print('\n'.join(map(''.join, itertools.permutations(map(str, range(1, int(input()) + 1))))))