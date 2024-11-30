################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 2 of AOC.               #
# Vers: 1.0.0 12/02/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    total = 0
    for line in lines:
        _, right = line.split(':')
        rounds = right.split(';')
        redmax = 0
        bluemax = 0
        greenmax = 0
        for round in rounds:
            boxes = round.split(',')
            redCount = 0
            blueCount = 0
            greenCount = 0
            for box in boxes:
                num, color = box.strip().split(' ')
                if color == 'red':
                    redCount += int(num)
                    redmax = max(redmax, int(num))
                elif color == 'green':
                    greenCount += int(num)
                    greenmax = max(greenmax, int(num))
                elif color == 'blue':
                    blueCount += int(num)
                    bluemax = max(bluemax, int(num))
        total += bluemax * redmax * greenmax

    print(total)
    return 0


if __name__ == '__main__':
    main()
