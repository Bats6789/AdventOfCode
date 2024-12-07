import sys


def search(grid, x, y, width, height):
    avoid = ['#', 'O']
    dir = 'up'
    seen = []
    while 0 <= x < width and 0 <= y < height:
        if dir == 'up':
            if y == 0:
                break
            if grid[y - 1][x] in avoid:
                dir = 'right'
            else:
                y -= 1
        if dir == 'down':
            if y == height - 1:
                break
            if grid[y + 1][x] in avoid:
                dir = 'left'
            else:
                y += 1
        if dir == 'right':
            if x == width - 1:
                break
            if grid[y][x + 1] in avoid:
                dir = 'down'
            else:
                x += 1
        if dir == 'left':
            if x == 0:
                break
            if grid[y][x - 1] in avoid:
                dir = 'up'
            else:
                x -= 1

        if (x, y, dir) in seen:
            return True
        else:
            seen.append((x, y, dir))

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

    for yp in range(height):
        for xp in range(width):
            if grid[yp][xp] == '.':
                grid[yp][xp] = '#'
                if search(grid, x, y, width, height):
                    count += 1
                grid[yp][xp] = '.'

    print(count)
    return 0


if __name__ == '__main__':
    main()
