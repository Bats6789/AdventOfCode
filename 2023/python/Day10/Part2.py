################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 10 of AOC.              #
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
    above = False
    below = False
    right = False
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
                    above = True
                if grid[row + 1][col] == '|' or grid[row + 1][col] == 'J' or grid[row + 1][col] == 'L':
                    queue.append((row + 1, col, dist + 1))
                    below = True
                if grid[row][col - 1] == '-' or grid[row][col - 1] == 'L' or grid[row][col - 1] == 'F':
                    queue.append((row, col - 1, dist + 1))
                if grid[row][col + 1] == '-' or grid[row][col + 1] == 'J' or grid[row][col + 1] == '7':
                    queue.append((row, col + 1, dist + 1))
                    right = True

                # Replace S with appropriate character
                if above:
                    if below:
                        grid[row][col] = '|'
                    elif right:
                        grid[row][col] = 'L'
                    else:  # above and left
                        grid[row][col] = 'J'
                elif right:
                    if below:
                        grid[row][col] = 'F'
                    else:  # right and left
                        grid[row][col] = '-'
                else:  # left and down
                    grid[row][col] = '7'

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

    for i, line in enumerate(distMap):
        inside = False
        seenUpPipe = 0
        for j, c in enumerate(line):
            if c == -1:
                grid[i][j] = 'I' if inside else 'O'
            else:
                match grid[i][j]:
                    case '|':
                        inside = not inside
                    case '-':
                        inside = inside
                    case 'J':
                        if seenUpPipe < 0:
                            inside = not inside

                        seenUpPipe = 0
                    case '7':
                        if seenUpPipe > 0:
                            inside = not inside

                        seenUpPipe = 0
                    case 'L':
                        seenUpPipe = 1
                    case 'F':
                        seenUpPipe = -1

    print(sum(row.count('I') for row in grid))

    return 0


if __name__ == '__main__':
    main()
