import sys
from itertools import pairwise


def getSeat(boardingPass):
    row = 0
    col = 0

    colStr = boardingPass[-3:]
    rowStr = boardingPass[:-3]

    for c in colStr:
        col <<= 1
        col += 1 if c == 'R' else 0

    for c in rowStr:
        row <<= 1
        row += 1 if c == 'B' else 0

    return col, row


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    locs = list(getSeat(line) for line in data.split('\n'))
    ids = sorted(list(row * 8 + col for col, row in locs))

    seatId = -1
    for id1, id2 in pairwise(ids):
        if id2 - id1 > 1:
            seatId = id1 + 1
            break

    print(seatId)
    return 0


if __name__ == '__main__':
    main()
