import sys
import heapq


def can_cheat(cheated, cheat, loc):
    return cheated is False and equal(cheat, loc)


def get(grid, pt):
    return grid[pt[1]][pt[0]]


def equal(left, right):
    return left[0] == right[0] and left[1] == right[1]


def solve(grid, start, stop, cheat):
    cheated = False
    visited = set()

    pq = []

    heapq.heappush(pq, (0, start))

    loc = start
    s = 0

    while len(pq) > 0 and not equal(loc, stop):
        s, loc = heapq.heappop(pq)

        if equal(loc, stop):
            break

        visited.add(loc)

        # up
        new_loc = (loc[0], loc[1] - 1)
        if (get(grid, new_loc) != '#' or can_cheat(cheated, cheat, new_loc)) and new_loc not in visited:
            if get(grid, new_loc) == '#':
                cheated = True
            heapq.heappush(pq, (s + 1, new_loc))
        # down
        new_loc = (loc[0], loc[1] + 1)
        if (get(grid, new_loc) != '#' or can_cheat(cheated, cheat, new_loc)) and new_loc not in visited:
            if get(grid, new_loc) == '#':
                cheated = True
            heapq.heappush(pq, (s + 1, new_loc))
        # left
        new_loc = (loc[0] - 1, loc[1])
        if (get(grid, new_loc) != '#' or can_cheat(cheated, cheat, new_loc)) and new_loc not in visited:
            if get(grid, new_loc) == '#':
                cheated = True
            heapq.heappush(pq, (s + 1, new_loc))
        # right
        new_loc = (loc[0] + 1, loc[1])
        if (get(grid, new_loc) != '#' or can_cheat(cheated, cheat, new_loc)) and new_loc not in visited:
            if get(grid, new_loc) == '#':
                cheated = True
            heapq.heappush(pq, (s + 1, new_loc))

    return s


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = list(list(line) for line in data.split('\n'))

    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el == 'S':
                start = (j, i)
            elif el == 'E':
                stop = (j, i)
    count = 0

    og = solve(grid, start, stop, (0, 0))

    for i, row in enumerate(grid):
        for j, el in enumerate(row):
            if el != '#' or j == 0 or i == 0 or j == len(grid[0]) - 1 or i == len(grid) - 1:
                continue

            cheat = (j, i)

            val = solve(grid, start, stop, cheat)

            if val < og and og - val >= 100:
                count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
