################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 21 of AOC.              #
# Vers: 1.0.0 12/21/2023 CBW - Original code.  #
################################################
import sys
from collections import deque


def fill(sc, sr, ss, grid):
    queue = deque([(sc, sr, ss)])
    ans = set()
    seen = {(sc, sr)}

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

    return len(ans)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(line) for line in data.split('\n')]

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c == 'S':
                start = (j, i)
                break

    steps = 26501365
    size = len(grid)
    grid_width = steps // size - 1

    odd = (grid_width // 2 * 2 + 1) ** 2
    even = ((grid_width + 1) // 2 * 2) ** 2

    odd_points = fill(start[0], start[1], size * 2 + 1, grid)
    even_points = fill(start[0], start[1], size * 2, grid)

    corner_t = fill(start[0], size - 1, size - 1, grid)
    corner_r = fill(0, start[1], size - 1, grid)
    corner_b = fill(start[0], 0, size - 1, grid)
    corner_l = fill(size - 1, start[1], size - 1, grid)

    small_tr = fill(0, size - 1, size // 2 - 1, grid)
    small_tl = fill(size - 1, size - 1, size // 2 - 1, grid)
    small_br = fill(0, 0, size // 2 - 1, grid)
    small_bl = fill(size - 1, 0, size // 2 - 1, grid)

    large_tr = fill(0, size - 1, 3 * size // 2 - 1, grid)
    large_tl = fill(size - 1, size - 1, 3 * size // 2 - 1, grid)
    large_br = fill(0, 0, 3 * size // 2 - 1, grid)
    large_bl = fill(size - 1, 0, 3 * size // 2 - 1, grid)

    cornerSum = corner_b + corner_l + corner_t + corner_r
    smallSum = small_tr + small_tl + small_br + small_bl
    largeSum = large_tr + large_tl + large_br + large_bl

    print(odd * odd_points + even * even_points + cornerSum +
          (grid_width + 1) * smallSum + grid_width * largeSum)

    return 0


if __name__ == '__main__':
    main()
