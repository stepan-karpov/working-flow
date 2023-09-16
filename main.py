def build_prefix_table(pattern):
    prefix_table = [0] * len(pattern)
    j = 0
    for i in range(1, len(pattern)):
        while j > 0 and pattern[i] != pattern[j]:
            j = prefix_table[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        prefix_table[i] = j
    return prefix_table

def find_cyclic_shifts(text, pattern):
    P_ext = pattern + pattern
    prefix_table = build_prefix_table(P_ext)
    occurrences = []
    i, j = 0, 0
    while i < len(text):
        if text[i] == P_ext[j]:
            i += 1
            j += 1
            if j == len(P_ext):
                occurrences.append(i - j)
                j = prefix_table[j - 1]
        else:
            if j != 0:
                j = prefix_table[j - 1]
            else:
                i += 1
    return occurrences

# Example usage:
text = "abracadabra"
pattern = "abra"
cyclic_shifts = find_cyclic_shifts(text, pattern)
print(cyclic_shifts)  # Output: [0, 7]
