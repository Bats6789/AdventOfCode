import sys
import heapq


def valid(point, step):
    return point[0] == '.' and point[1] is False


def ispath(grid, height, width):
    step = (0, (0, 0))
    q = []

    heapq.heappush(q, step)

    step = heapq.heappop(q)

    while step[1][0] != width - 1 or step[1][1] != height - 1:
        grid[step[1][1]][step[1][0]] = ('.', True)
        tmp = (step[0] + 1, (step[1][0] - 1, step[1][1]))
        if step[1][0] > 0 and tmp not in q and valid(grid[tmp[1][1]][tmp[1][0]], tmp[0]):
            grid[tmp[1][1]][tmp[1][0]] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = (step[0] + 1, (step[1][0] + 1, step[1][1]))
        if step[1][0] < width - 1 and tmp not in q and valid(grid[tmp[1][1]][tmp[1][0]], tmp[0]):
            grid[tmp[1][1]][tmp[1][0]] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = (step[0] + 1, (step[1][0], step[1][1] - 1))
        if step[1][1] > 0 and tmp not in q and valid(grid[tmp[1][1]][tmp[1][0]], tmp[0]):
            grid[tmp[1][1]][tmp[1][0]] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = (step[0] + 1, (step[1][0], step[1][1] + 1))
        if step[1][1] < height - 1 and tmp not in q and valid(grid[tmp[1][1]][tmp[1][0]], tmp[0]):
            grid[tmp[1][1]][tmp[1][0]] = ('.', True)
            heapq.heappush(q, tmp)

        if len(q) == 0:
            break
        step = heapq.heappop(q)

    return step[1][0] == width - 1 and step[1][1] == height - 1


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    height = 71
    width = 71

    grid = list(list(('.', False) for j in range(width)) for i in range(height))

    process = False
    for i, line in enumerate(data.split('\n')):
        if i == 1024:
            process = True
        x, y = line.split(',')
        x = int(x)
        y = int(y)

        grid[y][x] = ('#', True)
        if process and not ispath(grid, height, width):
            print(f"{x},{y}")
            break
        for i, row in enumerate(grid):
            for j, el in enumerate(row):
                if el[0] == '.':
                    grid[i][j] = ('.', False)

    return 0


if __name__ == '__main__':
    main()
