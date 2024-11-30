################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 4 of AOC.               #
# Vers: 1.0.0 12/04/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    scratchCardsWon = []
    for line in data.split('\n'):
        _, cards = line.split(':')

        winningNumbers, numbers = cards.split('|')
        numbers = numbers.split()
        winningNumbers = winningNumbers.split()

        # The number of scratch cards is 1 (for the original) plus the number of cards won previously
        scratchCardCount = 1
        if scratchCardsWon != []:
            scratchCardCount += scratchCardsWon.pop(0)

        # Determine the number of scratch cards won
        winCount = 0
        for item in numbers:
            if item in winningNumbers:
                if winCount >= len(scratchCardsWon):
                    scratchCardsWon.append(scratchCardCount)
                else:
                    scratchCardsWon[winCount] += scratchCardCount
                winCount += 1

        total += scratchCardCount

    print(total)
    return 0


if __name__ == '__main__':
    main()
