################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 10 of AOC.              #
# Vers: 1.0.0 12/10/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    queue = []

    lines = data.split('\n')
    grid = [[c for c in line] for line in lines]

    rowLoc = 0
    for i, row in enumerate(grid):
        if 'S' in row:
            rowLoc = i
            colLoc = row.index('S')

    queue.append((rowLoc, colLoc, 0))

    distMap = [[-1 for j in range(len(grid[0]))] for i in range(len(grid))]
    while queue != []:
        row, col, dist = queue.pop(0)

        if distMap[row][col] != -1:
            break

        c = grid[row][col]
        distMap[row][col] = dist
        match(c):
            case 'S':
                if grid[row - 1][col] == '|' or grid[row - 1][col] == '7' or grid[row - 1][col] == 'F':
                    queue.append((row - 1, col, dist + 1))
                if grid[row + 1][col] == '|' or grid[row + 1][col] == 'J' or grid[row + 1][col] == 'L':
                    queue.append((row + 1, col, dist + 1))
                if grid[row][col - 1] == '-' or grid[row][col - 1] == 'L' or grid[row][col - 1] == 'F':
                    queue.append((row, col - 1, dist + 1))
                if grid[row][col + 1] == '-' or grid[row][col + 1] == 'J' or grid[row][col + 1] == '7':
                    queue.append((row, col + 1, dist + 1))
            case '|':
                if distMap[row - 1][col] == -1:
                    queue.append((row - 1, col, dist + 1))
                else:
                    queue.append((row + 1, col, dist + 1))
            case 'F':
                if distMap[row + 1][col] == -1:
                    queue.append((row + 1, col, dist + 1))
                else:
                    queue.append((row, col + 1, dist + 1))
            case '7':
                if distMap[row + 1][col] == -1:
                    queue.append((row + 1, col, dist + 1))
                else:
                    queue.append((row, col - 1, dist + 1))
            case 'L':
                if distMap[row - 1][col] == -1:
                    queue.append((row - 1, col, dist + 1))
                else:
                    queue.append((row, col + 1, dist + 1))
            case '-':
                if distMap[row][col + 1] == -1:
                    queue.append((row, col + 1, dist + 1))
                else:
                    queue.append((row, col - 1, dist + 1))
            case 'J':
                if distMap[row][col - 1] == -1:
                    queue.append((row, col - 1, dist + 1))
                else:
                    queue.append((row - 1, col, dist + 1))

    print(distMap[row][col])

    return 0


if __name__ == '__main__':
    main()
