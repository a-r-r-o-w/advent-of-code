import sys

direction = sys.stdin.readline().strip()
sys.stdin.readline()

have = dict()

for line in sys.stdin.readlines():
    src, dests = [x.strip() for x in line.split("=")]
    dests = [x.strip() for x in dests[1:-1].split(',')]
    have[src] = dests

n = len(direction)
index = 0

x = 'AAA'

while x != 'ZZZ':
    if direction[index % n] == 'L':
        x = have[x][0]
    else:
        x = have[x][1]
    index += 1

print(f"Day 8 (Part 1): {index}")
