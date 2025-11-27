import sys
import heapq


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    facing  = 'e'
    score = 0
    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el == 'S':
                start = (j, i)
            if el == 'E':
                end = (j, i)

    pq = []
    loc = start
    heapq.heappush(pq, (1, 'e', (loc[0] + 1, loc[1])))
    heapq.heappush(pq, (1000, 'n', (loc[0], loc[1])))
    seen = {}
    while loc[0] != end[0] or loc[1] != end[1]:
        current_score, dir, loc = heapq.heappop(pq)
        if loc[0] == end[0] and loc[1] == end[1]:
            break
        seen[(loc, dir)] = True
        if dir == 'e':
            test = (loc[0] + 1, loc[1])
            if (test, dir) not in seen and test[0] < len(grid[0]) and grid[test[0]][test[1]] != '#':
                heapq.heappush(pq, (current_score + 1, 'e', test))
            if (loc, 'n') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'n', loc))
            if (loc, 's') not in seen:
                heapq.heappush(pq, (current_score + 1000, 's', loc))
        elif dir == 'w':
            test = (loc[0] - 1, loc[1])
            if (test, dir) not in seen and test[0] > 0 and grid[test[0]][test[1]] != '#':
                heapq.heappush(pq, (current_score + 1, 'w', test))
            if (loc, 'n') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'n', loc))
            if (loc, 's') not in seen:
                heapq.heappush(pq, (current_score + 1000, 's', loc))
        if dir == 's':
            test = (loc[0], loc[1] + 1)
            if (test, dir) not in seen and test[1] < len(grid) and grid[test[0]][test[1]] != '#':
                heapq.heappush(pq, (current_score + 1, 's', test))
            if (loc, 'w') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'w', loc))
            if (loc, 'e') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'e', loc))
        elif dir == 'n':
            test = (loc[0], loc[1] - 1)
            if (test, dir) not in seen and test[1] > 0 and grid[test[0]][test[1]] != '#':
                heapq.heappush(pq, (current_score + 1, 'n', test))
            if (loc, 'w') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'w', loc))
            if (loc, 'e') not in seen:
                heapq.heappush(pq, (current_score + 1000, 'e', loc))


    print(current_score)

    return 0


if __name__ == '__main__':
    main()
