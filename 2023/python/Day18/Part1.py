################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 18 of AOC.              #
# Vers: 1.0.0 12/18/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    dirs = []
    dists = []
    colors = []
    pos = (0, 0)
    top = 0
    bottom = 0
    leftMost = 0
    rightMost = 0
    for line in data.split('\n'):
        dir, dist, color = line.split()
        dist = int(dist)
        match(dir):
            case 'L':
                pos = (pos[0] - dist, pos[1])
            case 'R':
                pos = (pos[0] + dist, pos[1])
            case 'U':
                pos = (pos[0], pos[1] - dist)
            case 'D':
                pos = (pos[0], pos[1] + dist)
        leftMost = min(leftMost, pos[0])
        rightMost = max(rightMost, pos[0])
        top = min(top, pos[1])
        bottom = max(bottom, pos[1])
        dirs.append(dir)
        dists.append(dist)
        colors.append(color)

    width = rightMost - leftMost + 1
    height = bottom - top + 1
    # print(leftMost, rightMost, top, bottom)

    grid = [['.' for i in range(width)] for j in range(height)]

    start = (-leftMost, -top)
    pos = start
    for dir, dist in zip(dirs, dists):
        grid[pos[1]][pos[0]] = '#'

        match(dir):
            case 'L':
                for i in range(dist + 1):
                    grid[pos[1]][pos[0] - i] = '#'
                pos = (pos[0] - dist, pos[1])
            case 'R':
                for i in range(dist + 1):
                    grid[pos[1]][pos[0] + i] = '#'
                pos = (pos[0] + dist, pos[1])
            case 'U':
                for i in range(dist + 1):
                    grid[pos[1] - i][pos[0]] = '#'
                pos = (pos[0], pos[1] - dist)
            case 'D':
                for i in range(dist + 1):
                    grid[pos[1] + i][pos[0]] = '#'
                pos = (pos[0], pos[1] + dist)

    # for line in grid:
    #     print(''.join(line))

    queue = [(81, 46)]
    while queue:
        pos = queue.pop(0)

        if grid[pos[1]][pos[0]] == '#':
            continue

        grid[pos[1]][pos[0]] = '#'

        if pos[1] != 0 and grid[pos[1] - 1][pos[0]] != '#':
            queue.append((pos[0], pos[1] - 1))
        if pos[1] != len(grid) - 1 and grid[pos[1] + 1][pos[0]] != '#':
            queue.append((pos[0], pos[1] + 1))
        if pos[0] != 0 and grid[pos[1]][pos[0] - 1] != '#':
            queue.append((pos[0] - 1, pos[1]))
        if pos[0] != len(grid[0]) - 1 and grid[pos[1]][pos[0] + 1] != '#':
            queue.append((pos[0] + 1, pos[1]))
    # for row, line in enumerate(grid):
    #     inside = False
    #     prev = '.'
    #     for col, c in enumerate(line):
    #         if c == '#' and prev != '#':
    #             inside = not inside
    #
    #         prev = c
    #         if inside:
    #             grid[row][col] = '#'

    count = 0
    for line in grid:
        # print(''.join(line))
        count += line.count('#')

    print(count)
    return 0


if __name__ == '__main__':
    main()
