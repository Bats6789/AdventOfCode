################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 16 of AOC.              #
# Vers: 1.0.0 12/16/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')

    grid = [list(line) for line in lines]
    energizedMap = [['.' for x in line] for line in lines]

    pos = [0, 0, 'r']
    queue = [pos]

    while queue != []:
        x, y, dir = queue.pop(0)
        if energizedMap[y][x] == '.' or grid[y][x] != '|' and grid[y][x] != '-':
            match(grid[y][x]):
                case '.':
                    match(dir):
                        case 'l':
                            if x != 0:
                                queue.append([x - 1, y, dir])
                        case 'r':
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, dir])
                        case 'd':
                            if y != len(grid) - 1:
                                queue.append([x, y + 1, dir])
                        case 'u':
                            if y != 0:
                                queue.append([x, y - 1, dir])
                case '|':
                    match(dir):
                        case 'l':
                            if y != 0:
                                queue.append([x, y - 1, 'u'])
                            if y != len(grid) - 1:
                                queue.append([x, y + 1, 'd'])
                        case 'r':
                            if y != 0:
                                queue.append([x, y - 1, 'u'])
                            if y != len(grid) - 1:
                                queue.append([x, y + 1, 'd'])
                        case 'd':
                            if y != len(grid[0]) - 1:
                                queue.append([x, y + 1, dir])
                        case 'u':
                            if y != 0:
                                queue.append([x, y - 1, dir])
                case '-':
                    match(dir):
                        case 'l':
                            if x != 0:
                                queue.append([x - 1, y, dir])
                        case 'r':
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, dir])
                        case 'd':
                            if x != 0:
                                queue.append([x - 1, y, 'l'])
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, 'r'])
                        case 'u':
                            if x != 0:
                                queue.append([x - 1, y, 'l'])
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, 'r'])
                case '/':
                    match(dir):
                        case 'l':
                            if y != len(grid) - 1:
                                queue.append([x, y + 1, 'd'])
                        case 'r':
                            if y != 0:
                                queue.append([x, y - 1, 'u'])
                        case 'd':
                            if x != 0:
                                queue.append([x - 1, y, 'l'])
                        case 'u':
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, 'r'])
                case '\\':
                    match(dir):
                        case 'l':
                            if y != 0:
                                queue.append([x, y - 1, 'u'])
                        case 'r':
                            if y != len(grid) - 1:
                                queue.append([x, y + 1, 'd'])
                        case 'd':
                            if x != len(grid[0]) - 1:
                                queue.append([x + 1, y, 'r'])
                        case 'u':
                            if x != 0:
                                queue.append([x - 1, y, 'l'])
            energizedMap[y][x] = '#'

    # for line in energizedMap:
    #     print(''.join(line))
    count = 0
    for line in energizedMap:
        count += line.count('#')

    print(count)

    return 0


if __name__ == '__main__':
    main()
