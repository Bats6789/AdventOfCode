################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 9 of AOC.               #
# Vers: 1.0.0 12/09/2023 CBW - Original code.  #
################################################
import sys


def processEls(els):
    quit = True
    for el in els:
        if el != 0:
            quit = False

    if quit:
        return 0

    diffs = [b - a for a, b in zip(els[:-1:], els[1::])]

    return els[-1] + processEls(diffs)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')

    total = 0
    for line in lines:
        els = list(map(int, line.split()))
        total += processEls(els)
    print(total)
    return 0


if __name__ == '__main__':
    main()
