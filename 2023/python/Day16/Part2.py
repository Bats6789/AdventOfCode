################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 16 of AOC.              #
# Vers: 1.0.0 12/16/2023 CBW - Original code.  #
################################################
import sys


def travel(grid, pos):
    queue = [pos]

    energizedMap = [['.' for x in line] for line in grid]
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

    return count


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')

    grid = [list(line) for line in lines]

    count = 0
    for i in range(len(grid[0])):
        pos = [i, 0, 'd']
        newCount1 = travel(grid, pos)
        pos = [i, len(grid) - 1, 'u']
        newCount2 = travel(grid, pos)
        count = max(newCount1, newCount2, count)
    for i in range(len(grid)):
        pos = [0, i, 'r']
        newCount1 = travel(grid, pos)
        pos = [len(grid[0]) - 1, i, 'l']
        newCount2 = travel(grid, pos)
        count = max(newCount1, newCount2, count)

    print(count)

    return 0


if __name__ == '__main__':
    main()
