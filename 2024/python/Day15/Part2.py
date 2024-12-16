import sys

shift_list = []


def shift(grid, x, y, dx, dy):
    if grid[y][x] == '.':
        return True
    elif grid[y][x] == '#':
        return False
    elif dy == 0:
        if shift(grid, x + dx, y + dy, dx, dy):
            pt = ((y + dy, x + dx), (y, x))
            if pt not in shift_list:
                shift_list.append(pt)
            return True
        else:
            return False
    elif grid[y][x] == '[':
        if shift(grid, x + dx, y + dy, dx, dy) and shift(grid, x + dx + 1, y + dy, dx, dy):
            pt = ((y + dy, x + dx), (y, x))
            if pt not in shift_list:
                shift_list.append(pt)
            pt = ((y + dy, x + dx + 1), (y, x + 1))
            if pt not in shift_list:
                shift_list.append(pt)
            return True
        else:
            return False
    elif grid[y][x] == ']':
        if shift(grid, x + dx, y + dy, dx, dy) and shift(grid, x + dx - 1, y + dy, dx, dy):
            pt = ((y + dy, x + dx), (y, x))
            if pt not in shift_list:
                shift_list.append(pt)
            pt = ((y + dy, x + dx - 1), (y, x - 1))
            if pt not in shift_list:
                shift_list.append(pt)
            return True
        else:
            return False
    elif shift(grid, x + dx, y + dy, dx, dy):
        pt = ((y + dy, x + dx), (y, x))
        if pt not in shift_list:
            shift_list.append(pt)
        return True
    else:
        return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    mapping, actions = data.split('\n\n')

    grid = []
    for row in mapping.split('\n'):
        line = []
        for c in row:
            match c:
                case '#':
                    line += ['#', '#']
                case 'O':
                    line += ['[', ']']
                case '.':
                    line += ['.', '.']
                case '@':
                    line += ['@', '.']
        grid.append(line)

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
        global shift_list
        shift_list = []
        match action:
            case '^':
                if shift(grid, pos_x, pos_y, 0, -1):
                    for shifting in shift_list:
                        target = shifting[0]
                        source = shifting[1]
                        grid[target[0]][target[1]] = grid[source[0]][source[1]]
                        grid[source[0]][source[1]] = '.'
                    grid[pos_y][pos_x] = '.'
                    pos_y -= 1
                    grid[pos_y][pos_x] = '@'
            case '>':
                if shift(grid, pos_x, pos_y, 1, 0):
                    for shifting in shift_list:
                        target = shifting[0]
                        source = shifting[1]
                        grid[target[0]][target[1]] = grid[source[0]][source[1]]
                        grid[source[0]][source[1]] = '.'
                    grid[pos_y][pos_x] = '.'
                    pos_x += 1
                    grid[pos_y][pos_x] = '@'
            case '<':
                if shift(grid, pos_x, pos_y, -1, 0):
                    for shifting in shift_list:
                        target = shifting[0]
                        source = shifting[1]
                        grid[target[0]][target[1]] = grid[source[0]][source[1]]
                        grid[source[0]][source[1]] = '.'
                    grid[pos_y][pos_x] = '.'
                    pos_x -= 1
                    grid[pos_y][pos_x] = '@'
            case 'v':
                if shift(grid, pos_x, pos_y, 0, 1):
                    for shifting in shift_list:
                        target = shifting[0]
                        source = shifting[1]
                        grid[target[0]][target[1]] = grid[source[0]][source[1]]
                        grid[source[0]][source[1]] = '.'
                    grid[pos_y][pos_x] = '.'
                    pos_y += 1
                    grid[pos_y][pos_x] = '@'

    for i, line in enumerate(grid):
        for j, el in enumerate(line):
            if el == '[':
                total += 100 * i + j

    print(total)

    return 0


if __name__ == '__main__':
    main()
