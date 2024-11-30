################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 21 of AOC.              #
# Vers: 1.0.0 12/21/2023 CBW - Original code.  #
################################################
import sys
from collections import deque


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(line) for line in data.split('\n')]

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c == 'S':
                start = (j, i)
                break

    queue = deque([(start[0], start[1], 64)])
    ans = set()
    seen = {start}

    while queue:
        c, r, s = queue.popleft()

        if s % 2 == 0:
            ans.add((c, r))

        if s == 0:
            continue

        for nc, nr in [(c, r + 1), (c, r - 1), (c + 1, r), (c - 1, r)]:
            if nc < 0 or nc >= len(grid[0]) or nr < 0 or nr >= len(grid) or grid[nr][nc] == '#' or (nc, nr) in seen:
                continue
            seen.add((nc, nr))
            queue.append((nc, nr, s - 1))

    print(len(ans))
    return 0


if __name__ == '__main__':
    main()
