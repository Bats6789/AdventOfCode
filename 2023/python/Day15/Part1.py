################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 15 of AOC.              #
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

    ans = 0
    for chunk in data.split(','):
        ans += HASH(chunk)
    print(ans)
    return 0


if __name__ == '__main__':
    main()
