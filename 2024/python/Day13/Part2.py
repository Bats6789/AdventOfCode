import sys
import numpy as np


def get_wins(prize, a, b):
    coef = np.array([a, b]).T
    res = np.linalg.solve(coef, prize)
    res = np.round(res).astype(int)

    return 3 * res[0] + res[1] if np.all(np.matmul(coef, res) == prize) else 0


def parse(line):
    return np.array((tuple(int(s[2:]) for s in line.split(': ')[1].split(', '))))


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    games = data.split('\n\n')

    total = 0

    for game in games:
        a, b, prize = map(parse, game.split('\n'))
        prize += 10000000000000
        ans = get_wins(prize, a, b)
        total += ans

    print(total)
    return 0


if __name__ == '__main__':
    main()
