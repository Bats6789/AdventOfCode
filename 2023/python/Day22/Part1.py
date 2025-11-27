################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 22 of AOC.              #
# Vers: 1.0.0 12/22/2023 CBW - Original code.  #
################################################
import sys


class Brick:
    def __init__(self, start: str, stop: str):
        self.start = list(map(int, start.split(',')))
        self.stop = list(map(int, stop.split(',')))

    def __eq__(self, o):
        return self.start[2] == o.start[2]

    def __lt__(self, o):
        return self.start[2] < o.start[2]

    def __gt__(self, o):
        return self.start[2] > o.start[2]

    def __repr__(self):
        return f"start={self.start}, stop={self.stop}"

    def overlap(self, o):
        x1s, y1s, _ = self.start
        x1p, y1p, _ = self.stop
        x2s, y2s, _ = o.start
        x2p, y2p, _ = o.stop
        return max(x1s, x2s) <= min(x1p, x2p) and max(y1s, y2s) <= min(y1p, y2p)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    bricks = [Brick(line.split('~')[0], line.split('~')[1]) for line in data.split('\n')]

    bricks.sort()

    for i, brick in enumerate(bricks):
        maxZ = 1
        for check in bricks[:i]:
            if brick.overlap(check):
                maxZ = max(maxZ, check.stop[2] + 1)
        brick.stop[2] -= brick.start[2] - maxZ
        brick.start[2] = maxZ

    bricks.sort()

    supports = {i: set() for i in range(len(bricks))}
    supported = {i: set() for i in range(len(bricks))}

    for j, upper in enumerate(bricks):
        for i, lower in enumerate(bricks[:j]):
            if lower.overlap(upper) and lower.stop[2] + 1 == upper.start[2]:
                supports[i].add(j)
                supported[j].add(i)

    total = 0

    for i in range(len(bricks)):
        if all(len(supported[j]) >= 2 for j in supports[i]):
            total += 1

    print(total)
    return 0


if __name__ == '__main__':
    main()
