################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 13 of AOC.              #
# Vers: 1.0.0 12/13/2023 CBW - Original code.  #
################################################
import sys


def getMirror(notes):
    colCount = 999999
    rowCount = 999999
    for i in range(1, len(notes[0])):
        difference = 0
        for row in notes:
            row = list(row)
            above = row[i-1::-1]
            below = row[i:]
            for left, right in zip(above, below):
                if left != right:
                    difference += 1

        if difference == 1:
            colCount = i
            break

    newNotes = [''.join(x) for x in zip(*notes)]

    for i in range(1, len(newNotes[0])):
        difference = 0
        for row in newNotes:
            row = list(row)
            above = row[i-1::-1]
            below = row[i:]
            for left, right in zip(above, below):
                if left != right:
                    difference += 1

        if difference == 1:
            rowCount = i
            break

    return colCount if colCount < rowCount else 100 * rowCount


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    maps = data.split('\n\n')

    ans = 0
    for notes in maps:
        ans += getMirror(notes.split('\n'))

    print(ans)
    return 0


if __name__ == '__main__':
    main()
