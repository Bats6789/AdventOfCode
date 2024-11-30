################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 17 of AOC.              #
# Vers: 1.0.0 12/17/2023 CBW - Original code.  #
################################################
import sys
from heapq import heappush, heappop


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(map(int, list(line))) for line in data.split('\n')]
    stop = [len(grid[0]) - 1, len(grid) - 1]
    queue = [(0, 0, 0, 'n', 0)]
    seen = set()

    while queue:
        heatLoss, x, y, dir, steps = heappop(queue)
        # print(x, y)

        if [x, y] == stop:
            print(heatLoss)
            break

        match(dir):
            case 'n':
                nx = 0
                ny = 0
            case 'l':
                nx = x - 1
                ny = y
            case 'r':
                nx = x + 1
                ny = y
            case 'u':
                nx = x
                ny = y - 1
            case 'd':
                nx = x
                ny = y + 1

        if x < 0 or x >= len(grid[0]) or y < 0 or y >= len(grid):
            continue

        if (x, y, dir, steps) in seen:
            continue

        if steps < 10 and dir != 'n' and 0 <= nx < len(grid[0]) and 0 <= ny < len(grid):
            seen.add((x, y, dir, steps))
            heappush(queue, (heatLoss + grid[ny][nx], nx, ny, dir, steps + 1))

        if dir != 'u' and dir != 'd' and steps >= 4 or dir == 'n':
            if y > 0:
                heappush(queue, (heatLoss + grid[y - 1][x], x, y - 1, 'u', 1))
            if y < len(grid) - 1:
                heappush(queue, (heatLoss + grid[y + 1][x], x, y + 1, 'd', 1))

        if dir != 'l' and dir != 'r' and steps >= 4 or dir == 'n':
            if x > 0:
                heappush(queue, (heatLoss + grid[y][x - 1], x - 1, y, 'l', 1))
            if x < len(grid[0]) - 1:
                heappush(queue, (heatLoss + grid[y][x + 1], x + 1, y, 'r', 1))

    return 0


if __name__ == '__main__':
    main()
