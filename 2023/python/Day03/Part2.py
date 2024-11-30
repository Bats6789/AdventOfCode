################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 3 of AOC.               #
# Vers: 1.0.0 12/03/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    total = 0
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            numCount = 0
            countList = []
            top = 0
            bottom = 0
            left = 0
            right = 0
            topleft = 0
            topright = 0
            bottomleft = 0
            bottomright = 0
            if c == '*':
                # top
                if i > 0:
                    if lines[i - 1][j].isdigit():
                        top = 1
                        countList.append((i - 1, j))
                # bottom
                if i < len(lines) - 1:
                    if lines[i + 1][j].isdigit():
                        bottom = 1
                        countList.append((i + 1, j))
                # left
                if j > 0:
                    if lines[i][j - 1].isdigit():
                        left = 1
                        countList.append((i, j - 1))
                # right
                if j < len(line) - 1:
                    if lines[i][j + 1].isdigit():
                        right = 1
                        countList.append((i, j + 1))
                # topleft
                if i > 0 and j > 0 and top == 0:
                    if lines[i - 1][j - 1].isdigit():
                        topleft = 1
                        countList.append((i - 1, j - 1))
                # topright
                if i > 0 and j < len(line) - 1 and top == 0:
                    if lines[i - 1][j + 1].isdigit():
                        topright = 1
                        countList.append((i - 1, j + 1))
                # bottomleft
                if i < len(lines) - 1 and j > 0 and bottom == 0:
                    if lines[i + 1][j - 1].isdigit():
                        bottomleft = 1
                        countList.append((i + 1, j - 1))
                # bottomright
                if i < len(lines) - 1 and j < len(line) - 1 and bottom == 0:
                    if lines[i + 1][j + 1].isdigit():
                        bottomright = 1
                        countList.append((i + 1, j + 1))

                numCount = top + bottom + left + right + topleft + topright + bottomleft + bottomright

            if numCount >= 2:
                first = countList[0][1]
                row = countList[0][0]
                while lines[row][first].isdigit() and first > 0:
                    first -= 1
                if not lines[row][first].isdigit():
                    first += 1
                last = countList[0][1]
                while last < len(line) and lines[row][last].isdigit():
                    last += 1

                num1 = int(lines[row][first:last])

                first = countList[1][1]
                row = countList[1][0]
                while lines[row][first].isdigit() and first > 0:
                    first -= 1
                if not lines[row][first].isdigit():
                    first += 1
                last = countList[1][1]
                while last < len(line) and lines[row][last].isdigit():
                    last += 1

                num2 = int(lines[row][first:last])
                total += num1 * num2

    print(total)
    return 0


if __name__ == '__main__':
    main()
