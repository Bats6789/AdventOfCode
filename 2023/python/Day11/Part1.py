################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 11 of AOC.              #
# Vers: 1.0.0 12/11/2023 CBW - Original code.  #
################################################
import sys
import numpy as np
import math
import itertools


def getDistance(pt1, pt2):
    return int(math.fabs(pt1[0] - pt2[0]) + math.fabs(pt1[1] - pt2[1]))


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')

    newLines = []
    expandCols = []
    for line in lines:
        newLines.append(list(line))
        if '#' not in line:
            newLines.append(list(line))

    lines = np.array(newLines)
    for i in range(len(lines[0])):
        if '#' not in lines[:, i]:
            expandCols.append(i)

    grid = np.zeros((len(lines), len(lines[0]) + len(expandCols)), dtype=str)

    addCol = 0
    for i in range(len(lines[0])):
        grid[:, i + addCol] = lines[:, i]
        if i in expandCols:
            addCol += 1
            grid[:, i + addCol] = lines[:, i]

    planets = []
    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c == '#':
                planets.append((i, j))

    total = 0
    for a, b in itertools.combinations(planets, 2):
        total += getDistance(a, b)

    print(total)
    return 0


if __name__ == '__main__':
    main()
