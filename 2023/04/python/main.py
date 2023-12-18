import collections
import sys

wins_per_level = {}

for index, line in enumerate(sys.stdin):
    line = line.strip()
    win, have = line.split('|')
    
    win = set(map(int, win.split()[2:]))
    have = list(map(int, have.split()))
    freq_have = collections.Counter(have)
    wins_per_level[index] = 0
    
    for i in win:
        if i in freq_have.keys():
            wins_per_level[index] += freq_have[i]

total = 0
count = {i: 1 for i in range(index + 1)}
current_index = 0

while current_index in count.keys():
    total += count[current_index]
    for i in range(current_index + 1, min(index, current_index + wins_per_level[current_index]) + 1):
        count[i] += count[current_index]
    current_index += 1

print(f"Day 4 (Part 2): {total}")
