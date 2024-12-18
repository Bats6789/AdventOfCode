import sys
import heapq


def valid(point, step):
    return point[0] == '.' and point[1] is False

def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    height = 71
    width = 71

    grid = list(list(('.', False) for j in range(width)) for i in range(height))

    for i, line in enumerate(data.split('\n')):
        if i == 1024:
            break
        x, y = line.split(',')
        x = int(x)
        y = int(y)

        grid[y][x] = ('#', True)

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

        step = heapq.heappop(q)

    print(step[0])

    return 0


if __name__ == '__main__':
    main()
