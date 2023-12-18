import sys

direction = sys.stdin.readline().strip()
sys.stdin.readline()

have = dict()

for line in sys.stdin.readlines():
    src, dests = [x.strip() for x in line.split("=")]
    dests = [x.strip() for x in dests[1:-1].split(',')]
    have[src] = dests

n = len(direction)
start = []

for x in have.keys():
    if x[-1] == 'A':
        start.append(x)

ranges = []
for x in start:
    index = 0
    while x[-1] != 'Z':
        if direction[index % n] == 'L':
            x = have[x][0]
        else:
            x = have[x][1]
        index += 1
    ranges.append(index)

import math
answer = 1
for x in ranges:
    answer = math.lcm(x, answer)

print(f"Day 8 (Part 2): {answer}")
