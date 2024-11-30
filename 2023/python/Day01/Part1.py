################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 1 of AOC.               #
# Vers: 1.0.0 12/01/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    for s in data.split('\n'):
        isfirst = True
        first = 0
        last = 0

        for c in s:
            if c.isnumeric():
                if isfirst:
                    first = int(c)
                    isfirst = False
                last = int(c)

        total += first * 10 + last

    print(total)


if __name__ == '__main__':
    main()
