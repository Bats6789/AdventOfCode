import sys


def shift(grid, x, y, dx, dy):
    if grid[y][x] == '.':
        return True
    elif grid[y][x] == '#':
        return False

    if shift(grid, x + dx, y + dy, dx, dy):
        grid[y + dy][x + dx] = grid[y][x]
        return True
    else:
        return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid, actions = data.split('\n\n')

    grid = list(list(line) for line in grid.split('\n'))

    total = 0

    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == '@':
                pos_x = j
                pos_y = i
                break
        if el == '@':
            break

    for action in actions:
        match action:
            case '^':
                if shift(grid, pos_x, pos_y, 0, -1):
                    grid[pos_y][pos_x] = '.'
                    pos_y -= 1
                    grid[pos_y][pos_x] = '@'
            case '>':
                if shift(grid, pos_x, pos_y, 1, 0):
                    grid[pos_y][pos_x] = '.'
                    pos_x += 1
                    grid[pos_y][pos_x] = '@'
            case '<':
                if shift(grid, pos_x, pos_y, -1, 0):
                    grid[pos_y][pos_x] = '.'
                    pos_x -= 1
                    grid[pos_y][pos_x] = '@'
            case 'v':
                if shift(grid, pos_x, pos_y, 0, 1):
                    grid[pos_y][pos_x] = '.'
                    pos_y += 1
                    grid[pos_y][pos_x] = '@'

    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == 'O':
                total += 100 * i + j

    print(total)

    return 0


if __name__ == '__main__':
    main()
