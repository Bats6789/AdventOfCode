import sys


def traverse(grid, slope):
    treeCount = 0
    pos = [0, 0]

    width = len(grid[0])
    height = len(grid)

    while pos[1] < height:
        if grid[pos[1]][pos[0]] == '#':
            treeCount += 1
        pos[0] = (pos[0] + slope[0]) % width
        pos[1] += slope[1]

    return treeCount


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = data.split('\n')
    slopeProd = 1

    slopes = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]

    for slope in slopes:
        slopeProd *= traverse(grid, slope)

    print(slopeProd)

    return 0


if __name__ == '__main__':
    main()
