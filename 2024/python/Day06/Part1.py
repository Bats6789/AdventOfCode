import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    width = len(grid[0])
    height = len(grid)
    count = 1

    for i, line in enumerate(grid):
        if '^' in line:
            y = i
            x = line.index('^')
            break

    dir = 'up'

    while 0 <= x < width and 0 <= y < height:
        if grid[y][x] == '.':
            count += 1
            grid[y][x] = 'X'

        match dir:
            case 'up':
                if y > 0 and grid[y - 1][x] == '#':
                    dir = 'right'
                else:
                    y -= 1
            case 'down':
                if y < height - 1 and grid[y + 1][x] == '#':
                    dir = 'left'
                else:
                    y += 1
            case 'right':
                if x < width - 1 and grid[y][x + 1] == '#':
                    dir = 'down'
                else:
                    x += 1
            case 'left':
                if x > 0 and grid[y][x - 1] == '#':
                    dir = 'up'
                else:
                    x -= 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
