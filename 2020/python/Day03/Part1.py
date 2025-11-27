import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = data.split('\n')

    treeCount = 0
    pos = [0, 0]

    width = len(grid[0])
    height = len(grid)

    while pos[1] < height:
        if grid[pos[1]][pos[0]] == '#':
            treeCount += 1
        pos[0] = (pos[0] + 3) % width
        pos[1] += 1

    print(treeCount)

    return 0


if __name__ == '__main__':
    main()
