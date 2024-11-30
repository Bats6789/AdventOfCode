################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 18 of AOC.              #
# Vers: 1.0.0 12/18/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    pos = (0, 0)
    pts = [pos]
    dirMap = {0: 'R', 1: 'D', 2: 'L', 3: 'U'}
    b = 0
    for line in data.split('\n'):
        _, _, color = line.split()
        color = color[2:-1]
        dir = dirMap[int(color[-1])]
        dist = int(color[:-1], base=16)
        b += dist
        match(dir):
            case 'L':
                pos = (pos[0] - dist, pos[1])
            case 'R':
                pos = (pos[0] + dist, pos[1])
            case 'U':
                pos = (pos[0], pos[1] - dist)
            case 'D':
                pos = (pos[0], pos[1] + dist)
        pts.append(pos)
        # print(f"#{color} => {dir} {dist}")

    A = abs(sum(pts[i][1] * (pts[i - 1][0] - pts[(i + 1) % len(pts)][0]) for i in range(len(pts)))) // 2
    i = A - b // 2 + 1

    print(i + b)

    return 0


if __name__ == '__main__':
    main()
