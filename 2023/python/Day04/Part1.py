################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 4 of AOC.               #
# Vers: 1.0.0 12/04/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    for line in data.split('\n'):
        _, scratchCards = line.split(':')

        winningNumbers, numbers = scratchCards.split('|')
        numbers = numbers.split()
        winningNumbers = winningNumbers.split()

        score = 0
        for item in numbers:
            if item in winningNumbers:
                score += 1

        if score > 0:
            total += 2**(score - 1)

    print(total)
    return 0


if __name__ == '__main__':
    main()
