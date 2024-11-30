################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 14 of AOC.              #
# Vers: 1.0.0 12/14/2023 CBW - Original code.  #
################################################
import sys


def pushUp(grid, i, j):
    done = False
    while not done:
        if i == 0 or grid[i - 1][j] != '.':
            done = True
        else:
            grid[i][j], grid[i - 1][j] = grid[i - 1][j], grid[i][j]
            i -= 1
    pass


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(row) for row in data.split('\n')]
    height = len(grid)
    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == 'O' and i != 0:
                pushUp(grid, i, j)

    print(sum((height - i) * line.count('O') for i, line in enumerate(grid)))
    return 0


if __name__ == '__main__':
    main()
