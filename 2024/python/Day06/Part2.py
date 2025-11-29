import sys


def search(grid, x, y, width, height):
    dir = 'up'
    seen = set()
    while 0 <= x < width and 0 <= y < height:
        point = (x, y, dir)
        match dir:
            case 'up':
                if y > 0 and grid[y - 1][x] == '#':
                    if point in seen:
                        return True
                    else:
                        seen.add(point)
                    dir = 'right'
                else:
                    y -= 1
            case 'down':
                if y < height - 1 and grid[y + 1][x] == '#':
                    if point in seen:
                        return True
                    else:
                        seen.add(point)
                    dir = 'left'
                else:
                    y += 1
            case 'right':
                if x < width - 1 and grid[y][x + 1] == '#':
                    if point in seen:
                        return True
                    else:
                        seen.add(point)
                    dir = 'down'
                else:
                    x += 1
            case 'left':
                if x > 0 and grid[y][x - 1] == '#':
                    if point in seen:
                        return True
                    else:
                        seen.add(point)
                    dir = 'up'
                else:
                    x -= 1

    return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    width = len(grid[0])
    height = len(grid)
    count = 0

    for i, line in enumerate(grid):
        if '^' in line:
            y = i
            x = line.index('^')
            break

    grid[y][x] = 'X'
    dir = 'up'

    ys = y
    xs = x

    while 0 <= x < width and 0 <= y < height:
        if grid[y][x] == '.':
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

    x = xs
    y = ys

    for yp in range(height):
        for xp in range(width):
            if grid[yp][xp] == 'X':
                grid[yp][xp] = '#'
                if search(grid, x, y, width, height):
                    count += 1
                grid[yp][xp] = '.'

    print(count)
    return 0


if __name__ == '__main__':
    main()
