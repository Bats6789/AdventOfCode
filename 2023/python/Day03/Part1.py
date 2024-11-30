################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 3 of AOC.               #
# Vers: 1.0.0 12/03/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    num = 0
    total = 0
    skip = 0
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            isgood = False
            if skip > 0:
                skip -= 1
                continue

            if c.isdigit():
                # top
                if i > 0:
                    if lines[i - 1][j] != '.' and not lines[i - 1][j].isdigit():
                        isgood = True
                # bottom
                if i < len(lines) - 1:
                    if lines[i + 1][j] != '.' and not lines[i + 1][j].isdigit():
                        isgood = True
                # left
                if j > 0:
                    if lines[i][j - 1] != '.' and not lines[i][j - 1].isdigit():
                        isgood = True
                # right
                if j < len(line) - 1:
                    if lines[i][j + 1] != '.' and not lines[i][j + 1].isdigit():
                        isgood = True
                # topleft
                if i > 0 and j > 0:
                    if lines[i - 1][j - 1] != '.' and not lines[i - 1][j - 1].isdigit():
                        isgood = True
                # topright
                if i > 0 and j < len(line) - 1:
                    if lines[i - 1][j + 1] != '.' and not lines[i - 1][j + 1].isdigit():
                        isgood = True
                # bottomleft
                if i < len(lines) - 1 and j > 0:
                    if lines[i + 1][j - 1] != '.' and not lines[i + 1][j - 1].isdigit():
                        isgood = True
                # bottomright
                if i < len(lines) - 1 and j < len(line) - 1:
                    if lines[i + 1][j + 1] != '.' and not lines[i + 1][j + 1].isdigit():
                        isgood = True

            if isgood:
                first = j
                while line[first].isdigit() and first > 0:
                    first -= 1
                if not line[first].isdigit():
                    first += 1
                last = j
                while last < len(line) and line[last].isdigit():
                    last += 1

                num = int(line[first:last])
                # print(num)
                total += num
                skip = last - j

    print(total)
    return 0


if __name__ == '__main__':
    main()
