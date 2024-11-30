################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 12 of AOC.              #
# Vers: 1.0.0 12/12/2023 CBW - Original code.  #
################################################
import sys


memoize = {}


def getScore(row, coord, index, coordIndex, current):
    key = (index, coordIndex, current)
    if key in memoize:
        return memoize[key]

    if index == len(row):
        if coordIndex == len(coord) and current == 0:
            return 1
        elif coordIndex == len(coord) - 1 and coord[coordIndex] == current:
            return 1
        else:
            return 0

    ans = 0
    for c in ['.', '#']:
        if row[index] == c or row[index] == '?':
            if c == '.' and current == 0:
                ans += getScore(row, coord, index + 1, coordIndex, 0)
            elif c == '.' and current > 0 and coordIndex < len(coord) and coord[coordIndex] == current:
                ans += getScore(row, coord, index + 1, coordIndex + 1, 0)
            elif c == '#':
                ans += getScore(row, coord, index + 1, coordIndex, current + 1)

    memoize[key] = ans
    return ans


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    grid = []
    coords = []
    for line in lines:
        left, right = line.split()
        grid.append('?'.join([left, left, left, left, left]))
        tmp = ','.join([right, right, right, right, right])
        coords.append(list(map(int, tmp.split(','))))

    ans = 0

    for row, coord in zip(grid, coords):
        memoize.clear()
        score = getScore(row, coord, 0, 0, 0)
        # print(row, coord, score)
        ans += score

    print(ans)

    return 0


if __name__ == '__main__':
    main()
