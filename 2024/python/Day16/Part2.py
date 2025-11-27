import sys
import heapq


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el == 'S':
                start = (j, i)
            if el == 'E':
                end = (j, i)

    pq = []
    loc = start
    heapq.heappush(pq, (1, 'e', (loc[0] + 1, loc[1]), [start, (loc[0] + 1, loc[1])]))
    heapq.heappush(pq, (1000, 'n', (loc[0], loc[1]), [start]))
    seen = {}
    valid = set()
    best_score = 10**10
    while len(pq) > 0:
        current_score, dir, loc, path = heapq.heappop(pq)
        seen[(loc, dir)] = current_score
        if loc[0] == end[0] and loc[1] == end[1]:
            best_score = min(best_score, current_score)

            if current_score == best_score:
                for p in path:
                    valid.add(p)
            continue
        if dir == 'e':
            test = (loc[0] + 1, loc[1])
            if (test, dir) not in seen and test[0] < len(grid[0]) and grid[test[1]][test[0]] != '#':
                heapq.heappush(pq, (current_score + 1, 'e', test, [*path, test]))
            if (loc, 'n') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'n', loc, path.copy()))
            if (loc, 's') not in seen:
                heapq.heappush(pq, (current_score + 1000, 's', loc, path.copy()))
        elif dir == 'w':
            test = (loc[0] - 1, loc[1])
            if (test, dir) not in seen and test[0] > 0 and grid[test[1]][test[0]] != '#':
                heapq.heappush(pq, (current_score + 1, 'w', test, [*path, test]))
            if (loc, 'n') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'n', loc, [*path]))
            if (loc, 's') not in seen:
                heapq.heappush(pq, (current_score + 1000, 's', loc, [*path]))
        if dir == 's':
            test = (loc[0], loc[1] + 1)
            if (test, dir) not in seen and test[1] < len(grid) and grid[test[1]][test[0]] != '#':
                heapq.heappush(pq, (current_score + 1, 's', test, [*path, test]))
            if (loc, 'w') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'w', loc, [*path]))
            if (loc, 'e') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'e', loc, [*path]))
        elif dir == 'n':
            test = (loc[0], loc[1] - 1)
            if (test, dir) not in seen and test[1] > 0 and grid[test[1]][test[0]] != '#':
                heapq.heappush(pq, (current_score + 1, 'n', test, [*path, test]))
            if (loc, 'w') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'w', loc, [*path]))
            if (loc, 'e') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'e', loc, [*path]))

    print(len(valid))

    return 0


if __name__ == '__main__':
    main()
