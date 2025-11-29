################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 7 of AOC.               #
# Vers: 1.0.0 12/07/2023 CBW - Original code.  #
################################################
import sys
from functools import cmp_to_key


# Wild notes:
# 4 wilds is always a 5 of a kind
# 3 wilds will either be 4 of a kind or 5 of a kind
# 2 wilds will either be a 3 of a kind or better, but not a full house
# 1 wilds will either be a pair or higher, but not two pair
# wilds will never be found in two pairs
def getHand(a):
    vals = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 0 if c ==
            'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in a]

    jCount = a.count('J')
    threeCount = 0
    twoCount = 0
    for val in vals:
        count = vals.count(val)

        # counts without wilds
        if count == 3:
            threeCount += 1
        elif count == 2:
            twoCount += 1

        # wild counts
        if val == 0:
            if count >= 4:
                return 7
        else:
            count += jCount

        # count with wilds
        if count >= 4:
            return 2 + count

    # scale counts
    threeCount //= 3
    twoCount //= 2
    tmpJ = jCount

    # adjust counts to account for wilds
    if twoCount > 0 and tmpJ == 1:
        threeCount += 1
        twoCount -= 1
        tmpJ -= 1

    if tmpJ > 1:
        threeCount += 1
        twoCount -= 1
    elif threeCount > 0 and tmpJ > 0:
        twoCount += 1

    # Full house and three of a kind
    if threeCount > 0:
        return 4 + twoCount

    # Remaining combinations
    return twoCount + jCount


def cmp_items(a, b):
    aC = a[0]
    bC = b[0]

    aVal = getHand(aC)
    bVal = getHand(bC)

    aList = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 0 if c ==
             'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in aC]
    bList = [int(c) if '1' < c <= '9' else 14 if c == 'A' else 10 if c == 'T' else 0 if c ==
             'J' else 12 if c == 'Q' else 13 if c == 'K' else 0 for c in bC]

    if aVal < bVal:
        return -1
    elif aVal > bVal:
        return 1
    else:
        for left, right in zip(aList, bList):
            if left > right:
                return 1
            elif left < right:
                return -1
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
