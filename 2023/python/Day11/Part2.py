################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 11 of AOC.              #
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

    lines = np.array(list(map(list, data.split('\n'))))

    expandCols = 0
    expandRows = 0
    planets = []
    ogPlanets = []
    scale = 999999
    for i, line in enumerate(lines):
        if '#' not in line:
            expandRows += 1
        expandCols = 0
        for j, c in enumerate(line):
            if '#' not in lines[:, j]:
                expandCols += 1
            if c == '#':
                ogPlanets.append((i, j))
                planets.append((i + expandRows * scale,
                                j + expandCols * scale))

    total = 0
    for a, b in itertools.combinations(planets, 2):
        total += getDistance(a, b)

    print(total)
    return 0


if __name__ == '__main__':
    main()
