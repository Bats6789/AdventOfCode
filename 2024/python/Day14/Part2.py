import sys
import numpy as np


def robots_to_str(robots):
    grid = list(list(' ' for _ in range(101)) for _ in range(103))

    for robot in robots:
        p, _ = robot
        grid[p[1]][p[0]] = '#'

    return '\n'.join("".join(line) for line in grid)


def print_robots(robots):
    grid = list(list(' ' for _ in range(101)) for _ in range(103))

    for robot in robots:
        p, _ = robot
        grid[p[1]][p[0]] = '#'

    print('\n'.join("".join(line) for line in grid))


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    robots = []

    for line in data.split('\n'):
        p, v = line.split(' ')
        p = p.split('=')[1]
        v = v.split('=')[1]

        p = np.array(list(map(int, p.split(','))))
        v = np.array(list(map(int, v.split(','))))

        robots.append((p, v))

    height = 103
    width = 101
    max_bot_line_count = 0
    for num in range(10000):
        for i, robot in enumerate(robots):
            p, v = robot
            p += v
            if p[0] < 0:
                p[0] += width
            elif p[0] >= width:
                p[0] -= width
            if p[1] < 0:
                p[1] += height
            elif p[1] >= height:
                p[1] -= height
        string = robots_to_str(robots)
        count = 0
        for row in string.split('\n'):
            start = 0
            for i, el in enumerate(row):
                if el == '#':
                    if start == 0:
                        start = i
                elif start != 0:
                    count = max(count, i - start)
                    start = 0

        if count > max_bot_line_count:
            max_bot_line_count = count
            seen = num + 1

    print(seen)

    return 0


if __name__ == '__main__':
    main()
