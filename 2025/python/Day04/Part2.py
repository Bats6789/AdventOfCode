import sys


def removeX(grid):
    for i, row in enumerate(grid):
        for j, val in enumerate(row):
            if val == 'x':
                grid[i][j] = '.'


def adjacent(grid, row, col):
    count = 0

    if row > 0:
        if col > 0 and grid[row - 1][col - 1] != '.':
            count += 1
        if grid[row - 1][col] != '.':
            count += 1
        if col < len(grid[0]) - 1 and grid[row - 1][col + 1] != '.':
            count += 1

    if col > 0 and grid[row][col - 1] != '.':
        count += 1
    if col < len(grid[0]) - 1 and grid[row][col + 1] != '.':
        count += 1

    if row < len(grid) - 1:
        if col > 0 and grid[row + 1][col - 1] != '.':
            count += 1
        if grid[row + 1][col] != '.':
            count += 1
        if col < len(grid[0]) - 1 and grid[row + 1][col + 1] != '.':
            count += 1

    return count


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    grid = list(list(line) for line in data.split('\n'))

    count = 0
    found = True

    while found:
        found = False
        for i, row in enumerate(grid):
            for j, val in enumerate(row):
                if val == '@' and adjacent(grid, i, j) < 4:
                    grid[i][j] = 'x'
                    found = True
                    count += 1

        if found:
            removeX(grid)

    print(count)

    return 0


if __name__ == '__main__':
    main()
