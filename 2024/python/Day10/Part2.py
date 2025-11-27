import sys


def walk(grid, pt, val):
    if val == 9:
        return 1

    total = 0
    if pt[0] > 0 and grid[pt[1]][pt[0] - 1] == chr(val + ord('0') + 1):
        total += walk(grid, (pt[0] - 1, pt[1]), val + 1)

    if pt[0] < len(grid[0]) - 1 and grid[pt[1]][pt[0] + 1] == chr(val + ord('0') + 1):
        total += walk(grid, (pt[0] + 1, pt[1]), val + 1)

    if pt[1] < len(grid) - 1 and grid[pt[1] + 1][pt[0]] == chr(val + ord('0') + 1):
        total += walk(grid, (pt[0], pt[1] + 1), val + 1)

    if pt[1] > 0 and grid[pt[1] - 1][pt[0]] == chr(val + ord('0') + 1):
        total += walk(grid, (pt[0], pt[1] - 1), val + 1)

    return total


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    pts = []
    total = 0

    for i, line in enumerate(grid):
        for j, c in enumerate(line):
            if c == '0':
                pts.append((j, i))

    global seen
    for pt in pts:
        total += walk(grid, pt, 0)

    print(total)

    return 0


if __name__ == '__main__':
    main()
