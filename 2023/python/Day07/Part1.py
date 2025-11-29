################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 7 of AOC.               #
# Vers: 1.0.0 12/07/2023 CBW - Original code.  #
################################################
import sys
from functools import cmp_to_key


def getHand(a):
    vals = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 11 if c ==
            'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in a]

    three = False
    two = False
    twoCount = 0
    for val in vals:
        count = vals.count(val)
        if count >= 4:
            return 2 + count
        elif count == 3:
            three = True
        elif count == 2:
            two = True
            twoCount += 1

    if three:
        return 4 + two

    twoCount //= 2
    return 1 + twoCount


def cmp_items(a, b):
    aC = a[0]
    bC = b[0]

    aVal = getHand(aC)
    bVal = getHand(bC)

    aList = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 11 if c ==
             'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in aC]
    bList = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 11 if c ==
             'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in bC]

    if aVal != bVal:
        return aVal - bVal
    else:
        for left, right in zip(aList, bList):
            if left != right:
                return left - right
        return 0


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    players = []
    for line in data.split('\n'):
        card, bid = line.strip().split()
        players.append([card, int(bid)])

    players = sorted(players, key=cmp_to_key(cmp_items))

    ans = 0
    bids = [bid for _, bid in players]
    for rank, score in enumerate(bids):
        ans += (rank + 1) * score

    print(ans)

    return 0


if __name__ == '__main__':
    main()
