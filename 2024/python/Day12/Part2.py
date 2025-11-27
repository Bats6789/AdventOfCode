import sys


seen = {}


def region(grid, x, y, el):
    area = 1
    perm = 0

    seen[(x, y)] = True

    if y > 0 and grid[y - 1][x] == el and (x, y - 1) not in seen:
        tmpP, tmpA = region(grid, x, y - 1, el)
        perm += tmpP
        area += tmpA

    if x > 0 and grid[y][x - 1] == el and (x - 1, y) not in seen:
        tmpP, tmpA = region(grid, x - 1, y, el)
        perm += tmpP
        area += tmpA

    if y < len(grid) - 1 and grid[y + 1][x] == el and (x, y + 1) not in seen:
        tmpP, tmpA = region(grid, x, y + 1, el)
        perm += tmpP
        area += tmpA

    if x < len(grid[0]) - 1 and grid[y][x + 1] == el and (x + 1, y) not in seen:
        tmpP, tmpA = region(grid, x + 1, y, el)
        perm += tmpP
        area += tmpA

    # top left
    if (y == 0 or grid[y - 1][x] != el) and (x == 0 or grid[y][x - 1] != el):
        perm += 1
    # top right
    if (y == 0 or grid[y - 1][x] != el) and (x == len(grid[0]) - 1 or grid[y][x + 1] != el):
        perm += 1
    # bottom left
    if (y == len(grid) - 1 or grid[y + 1][x] != el) and (x == 0 or grid[y][x - 1] != el):
        perm += 1
    # bottom right
    if (y == len(grid) - 1 or grid[y + 1][x] != el) and (x == len(grid[0]) - 1 or grid[y][x + 1] != el):
        perm += 1

    # top left
    if (y > 0 and grid[y - 1][x] == el) and (x > 0 and grid[y][x - 1] == el) and (grid[y - 1][x - 1] != el):
        perm += 1
    # top right
    if (y > 0 and grid[y - 1][x] == el) and (x < len(grid[0]) - 1 and grid[y][x + 1] == el) and (grid[y - 1][x + 1] != el):
        perm += 1
    # bottom left
    if (y < len(grid) - 1 and grid[y + 1][x] == el) and (x > 0 and grid[y][x - 1] == el) and (grid[y + 1][x - 1] != el):
        perm += 1
    # bottom right
    if (y < len(grid) - 1 and grid[y + 1][x] == el) and (x < len(grid[0]) - 1 and grid[y][x + 1] == el) and (grid[y + 1][x + 1] != el):
        perm += 1

    return perm, area


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    total = 0

    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if (j, i) not in seen:
                perm, area = region(grid, j, i, el)
                total += perm * area

    print(total)
    return 0


if __name__ == '__main__':
    main()
