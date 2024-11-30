################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 14 of AOC.              #
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


def pushLeft(grid, i, j):
    done = False
    while not done:
        if j == 0 or grid[i][j - 1] != '.':
            done = True
        else:
            grid[i][j], grid[i][j - 1] = grid[i][j - 1], grid[i][j]
            j -= 1
    pass


def pushDown(grid, i, j):
    done = False
    while not done:
        if i == len(grid) - 1 or grid[i + 1][j] != '.':
            done = True
        else:
            grid[i][j], grid[i + 1][j] = grid[i + 1][j], grid[i][j]
            i += 1
    pass


def pushRight(grid, i, j):
    done = False
    while not done:
        if j == len(grid[0]) - 1 or grid[i][j + 1] != '.':
            done = True
        else:
            grid[i][j], grid[i][j + 1] = grid[i][j + 1], grid[i][j]
            j += 1
    pass


def cycle(grid):
    # north
    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == 'O' and i != 0:
                pushUp(grid, i, j)
    # west
    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == 'O' and j != 0:
                pushLeft(grid, i, j)
    # South
    for i, line in reversed(list(enumerate(grid))):
        for j, el in enumerate(line):
            if el == 'O' and i != len(grid) - 1:
                pushDown(grid, i, j)
    # east
    for i, line in enumerate(grid):
        for j, el in reversed(list(enumerate(line))):
            if el == 'O' and j != len(grid[0]) - 1:
                pushRight(grid, i, j)

    pass


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    seen = {data}
    array = [data]
    grid = [list(row) for row in data.split('\n')]
    height = len(grid)
    for loop in range(1000000000):

        cycle(grid)

        tmpGrid = '\n'.join([''.join(line) for line in grid])
        if tmpGrid in seen:
            iter = loop + 1
            first = array.index(tmpGrid)
            break
        else:
            seen.add(tmpGrid)
            array.append(tmpGrid)

    tmpGrid = array[(1000000000 - first) % (iter - first) + first]
    grid = [list(row) for row in tmpGrid.split('\n')]
    # print('\n'.join([''.join(line) for line in grid]))
    print(sum((height - i) * line.count('O') for i, line in enumerate(grid)))
    return 0


if __name__ == '__main__':
    main()
