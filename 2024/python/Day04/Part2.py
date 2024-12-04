import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = data.split('\n')
    count = 0

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if i == 0 or j == 0 or i == len(grid) - 1 or j == len(row) - 1:
                continue

            if c == 'A':
                diag1 = "".join(grid[i + k][j + k] for k in range(-1, 2))
                diag2 = "".join(grid[i - k][j + k] for k in range(-1, 2))

                if (diag1 == 'MAS' or diag1 == 'SAM') and (diag2 == 'MAS' or diag2 == 'SAM'):
                    count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
