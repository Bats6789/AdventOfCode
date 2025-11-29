################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 6 of AOC.               #
# Vers: 1.0.0 12/06/2023 CBW - Original code.  #
################################################
import sys
import math


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    time, dist = data.split('\n')
    time = list(map(int, time.split(':')[1].strip().split()))
    dist = list(map(int, dist.split(':')[1].strip().split()))

    ans = 1
    for t, d in zip(time, dist):
        # let d be the distance traveled after button is released
        # let t be the time the button is held
        # let speed be the speed the boat travels
        # d = speed * (time - t)
        # speed = t
        # d = t * (time - t) = time * t - t^2
        # we want d > dist, so we want
        # -t^2 + time * t > dist
        # The problem is an upside down parabola.
        # There should be two points that intersect dist,
        #   the range between those two points is our answer.
        # So find the points where d = dist
        # -t^2 + time * t = dist
        # -t^2 + time * t - dist = 0
        # Use the quadratic equation
        # t = [-time +- sqrt(time^2 - 4(-1)(-dist))]/(-2)
        # t = [time +- sqrt(time^2 - 4dist)]/2
        # start = t1 = 0.5 * [time - sqrt(time^2 - 4dist)]
        # stop  = t2 = 0.5 * [time + sqrt(time^2 - 4dist)]
        # start < t < stop
        start = math.ceil(0.5 * (t - (t**2 - 4 * d)**0.5))
        stop = math.floor(0.5 * (t + (t**2 - 4 * d)**0.5))
        ans *= (stop - start + 1)
    print(ans)

    return 0


if __name__ == '__main__':
    main()
