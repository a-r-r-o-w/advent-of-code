import sys

# ATLEAST = 7
# ATMOST = 27
ATLEAST = 200000000000000
ATMOST = 400000000000000

positions = []
velocities = []
count = 0

for line in sys.stdin.readlines():
    line = line.strip().split("@")
    positions.append(list(map(int, line[0].split(","))))
    velocities.append(list(map(int, line[1].split(","))))

for index1, (pos1, vel1) in enumerate(zip(positions, velocities)):
    for index2, (pos2, vel2) in enumerate(zip(positions, velocities)):
        if index2 <= index1:
            continue
        try:
            t2 = (vel1[1] * (pos1[0] - pos2[0]) - vel1[0] * (pos1[1] - pos2[1])) / (vel2[0] * vel1[1] - vel1[0] * vel2[1])
            t1 = (vel2[1] * t2 - (pos1[1] - pos2[1])) / vel1[1]
            if t1 < 0 or t2 < 0:
                continue
            X = pos2[0] + vel2[0] * t2
            Y = pos2[1] + vel2[1] * t2
            if X < ATLEAST or X > ATMOST or Y < ATLEAST or Y > ATMOST:
                continue
            count += 1
            # print(index1, index2, pos1, pos2, t2, X, Y)
        except ZeroDivisionError:
            pass

print(f"Day 24 (Part 1): {count}")
