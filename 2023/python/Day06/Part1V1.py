################################################
# File: Part1V1.py                             #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 6 of AOC.               #
# Vers: 1.0.0 12/06/2023 CBW - Original code.  #
################################################
import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    time, dist = data.split('\n')
    time = list(map(int, time.split(':')[1].strip().split()))
    dist = list(map(int, dist.split(':')[1].strip().split()))

    ans = 1
    for t, d in zip(time, dist):
        firstPass = True
        # print(t,d)
        for i in range(t + 1):
            tmp = i * (t - i)
            if tmp > d:
                if firstPass:
                    firstPass = False
                    start = i
                stop = i
        # print(stop,start)
        ans *= (stop + 1 - start)
    print(ans)

    return 0


if __name__ == '__main__':
    main()
