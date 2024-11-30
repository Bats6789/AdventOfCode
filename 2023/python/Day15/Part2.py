################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 15 of AOC.              #
# Vers: 1.0.0 12/15/2023 CBW - Original code.  #
################################################
import sys


def HASH(str):
    value = 0

    for c in str:
        value += ord(c)
        value *= 17
    return value % 256


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    boxes = [[] for i in range(256)]

    ans = 0
    for chunk in data.split(','):
        if '=' in chunk:
            found = False
            key = HASH(chunk.split('=')[0])
            for i, box in enumerate(boxes[key]):
                if chunk.split('=')[0] == box.split()[0]:
                    boxes[key][i] = chunk.split('=')[0] + ' ' + chunk.split('=')[1]
                    found = True
                    break
            if not found:
                boxes[key].append(chunk.split('=')[0] + ' ' + chunk.split('=')[1])
        elif '-' in chunk:
            key = HASH(chunk.split('-')[0])
            for i, box in enumerate(boxes[key]):
                if chunk.split('-')[0] == box.split()[0]:
                    boxes[key].pop(i)
                    break
        else:
            print('uhoh')

    for i, box in enumerate(boxes):
        for j, lense in enumerate(box):
            ans += (i + 1) * (j + 1) * int(lense.split()[1])

    print(ans)
    return 0


if __name__ == '__main__':
    main()
