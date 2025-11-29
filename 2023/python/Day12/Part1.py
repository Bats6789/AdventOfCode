################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 12 of AOC.              #
# Vers: 1.0.0 12/12/2023 CBW - Original code.  #
################################################
import sys


def isValid(line, coord):
    broken = False
    count = 0
    coordCopy = coord.copy()
    for c in line:
        if c == '#':
            if broken:
                count += 1
            else:
                broken = True
                count = 1
        elif c == '.' and broken is True:
            if coordCopy == []:
                return False
            isBrokenCount = coordCopy.pop(0)
            if count != isBrokenCount:
                return False
            broken = False
    if broken is True:
        if coordCopy == []:
            return False
        isBrokenCount = coordCopy.pop(0)
        if count != isBrokenCount:
            return False

    return coordCopy == []


def getScore(row, coord, index):
    if '?' not in row:
        # print(row, coord, isValid(row, coord))
        return 1 if isValid(row, coord) else 0

    if row[index] == '?':
        newRow1 = row[:index] + '.' + row[index + 1:]
        newRow2 = row[:index] + '#' + row[index + 1:]
        return getScore(newRow1, coord, index + 1) + getScore(newRow2, coord, index + 1)
    else:
        return getScore(row, coord, index + 1)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    grid = [line.split()[0] for line in lines]
    coords = [list(map(int, line.split()[1].split(','))) for line in lines]

    ans = 0

    for row, coord in zip(grid, coords):
        score = getScore(row, coord, 0)
        # print(row, coord, score)
        ans += score

    print(ans)

    return 0


if __name__ == '__main__':
    main()
