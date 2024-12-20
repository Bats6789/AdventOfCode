# Solution borrowed from HyperNeutrino (https://www.youtube.com/watch?v=tWhwcORztSY)
import sys


def equal(left, right):
    return left[0] == right[0] and left[1] == right[1]


def get_critical_points(grid):
    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el == 'S':
                start = (j, i)
            elif el == 'E':
                stop = (j, i)

    return (start, stop)


def get_distances(grid, start, stop):
    dist = list(list(-1 for _ in range(len(grid[0]))) for _ in range(len(grid)))
    dist[start[1]][start[0]] = 0
    loc = start

    while not equal(loc, stop):
        tmp = (loc[0] - 1, loc[1])
        if loc[0] > 0 and dist[tmp[1]][tmp[0]] == -1 and grid[tmp[1]][tmp[0]] != '#':
            dist[tmp[1]][tmp[0]] = dist[loc[1]][loc[0]] + 1
            loc = tmp
        tmp = (loc[0] + 1, loc[1])
        if loc[0] < len(grid[0]) - 1 and dist[tmp[1]][tmp[0]] == -1 and grid[tmp[1]][tmp[0]] != '#':
            dist[tmp[1]][tmp[0]] = dist[loc[1]][loc[0]] + 1
            loc = tmp
        tmp = (loc[0], loc[1] - 1)
        if loc[1] > 0 and dist[tmp[1]][tmp[0]] == -1 and grid[tmp[1]][tmp[0]] != '#':
            dist[tmp[1]][tmp[0]] = dist[loc[1]][loc[0]] + 1
            loc = tmp
        tmp = (loc[0], loc[1] + 1)
        if loc[1] < len(grid) - 1 and dist[tmp[1]][tmp[0]] == -1 and grid[tmp[1]][tmp[0]] != '#':
            dist[tmp[1]][tmp[0]] = dist[loc[1]][loc[0]] + 1
            loc = tmp

    return dist


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    start, stop = get_critical_points(grid)

    count = 0

    dist = get_distances(grid, start, stop)

    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el == '#':
                continue
            for radius in range(2, 21):
                for dr in range(radius + 1):
                    dc = radius - dr
                    for nr, nc in {(i + dr, j + dc), (i + dr, j - dc), (i - dr, j + dc), (i - dr, j - dc)}:
                        if nr < 0 or nc < 0 or nr >= len(grid) or nc >= len(grid[0]):
                            continue
                        if grid[nr][nc] == '#':
                            continue
                        if dist[i][j] - dist[nr][nc] >= 100 + radius:
                            count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
