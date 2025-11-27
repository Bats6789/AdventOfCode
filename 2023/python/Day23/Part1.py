################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 23 of AOC.              #
# Vers: 1.0.0 12/23/2023 CBW - Original code.  #
################################################
import sys
from collections import deque


def maxPath(grid, start):
    q = deque([start])
    seen = set()

    maxStep = 0
    prev = '.'
    while q:
        # print(q)
        x, y, step = q.popleft()

        if prev != '.':
            isBranch = False
            if x > 0 and grid[y][x - 1] == '<':
                tmp = maxPath(grid, (x - 2, y, step + 2))
                maxStep = max(maxStep, tmp)
                isBranch = True

            if y > 0 and grid[y - 1][x] == '^':
                tmp = maxPath(grid, (x, y - 2, step + 2))
                maxStep = max(maxStep, tmp)
                isBranch = True

            if y < len(grid) - 1 and grid[y + 1][x] == 'v':
                tmp = maxPath(grid, (x, y + 2, step + 2))
                maxStep = max(maxStep, tmp)
                isBranch = True

            if x < len(grid[0]) - 1 and grid[y][x + 1] == '>':
                tmp = maxPath(grid, (x + 2, y, step + 2))
                maxStep = max(maxStep, tmp)
                isBranch = True

            if isBranch:
                break

        prev = grid[y][x]

        seen.add((x, y))

        if x > 0 and ((x - 1, y) not in seen)\
                and (grid[y][x - 1] == '.' or grid[y][x - 1] == '<'):
            q.append((x - 1, y, step + 1))

        if y > 0 and ((x, y - 1) not in seen)\
           and (grid[y - 1][x] == '.' or grid[y - 1][x] == '^'):
            q.append((x, y - 1, step + 1))

        if y < len(grid) - 1 and ((x, y + 1) not in seen)\
           and (grid[y + 1][x] == '.' or grid[y + 1][x] == 'v'):
            q.append((x, y + 1, step + 1))

        if x < len(grid[0]) - 1 and ((x + 1, y) not in seen)\
                and (grid[y][x + 1] == '.' or grid[y][x + 1] == '>'):
            q.append((x + 1, y, step + 1))

    return max(maxStep, step)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(line) for line in data.split('\n')]

    start = (1, 0, 0)

    print(maxPath(grid, start))

    return 0


if __name__ == '__main__':
    main()
