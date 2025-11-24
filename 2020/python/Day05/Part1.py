import sys


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
    ids = list(row * 8 + col for col, row in locs)

    print(max(ids))
    return 0


if __name__ == '__main__':
    main()
