import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = data.split('\n')
    count = 0

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c == 'X':
                # Search right
                if j < len(row) - 3 and "".join(row[j:j + 4]) == 'XMAS':
                    count += 1
                # Search Left
                if j > 2 and "".join(row[j - 3:j + 1]) == 'SAMX':
                    count += 1
                # Search up
                if i > 2 and "".join(col[j] for col in grid[i - 3:i + 1]) == 'SAMX':
                    count += 1
                # Search down
                if i < len(grid) - 3 and "".join(col[j] for col in grid[i:i + 4]) == 'XMAS':
                    count += 1
                # Search left up
                if j > 2 and i > 2 and "".join(grid[i - k][j - k] for k in range(4)) == 'XMAS':
                    count += 1
                # Search right up
                if j < len(row) - 3 and i > 2 and "".join(grid[i - k][j + k] for k in range(4)) == 'XMAS':
                    count += 1
                # Search left down
                if j > 2 and i < len(grid) - 3 and "".join(grid[i + k][j - k] for k in range(4)) == 'XMAS':
                    count += 1
                # Search right down
                if j < len(row) - 3 and i < len(grid) - 3 and "".join(grid[i + k][j + k] for k in range(4)) == 'XMAS':
                    count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
