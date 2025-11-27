################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 23 of AOC.              #
# Vers: 1.0.0 12/23/2023 CBW - Original code.  #
################################################
import sys


seen = set()


def dfs(pt, graph, end):
    if pt == end:
        return 0

    m = -float("inf")

    seen.add(pt)
    for edgePt in graph[pt]:
        if edgePt not in seen:
            m = max(m, dfs(edgePt, graph, end) + graph[pt][edgePt])
    seen.remove(pt)

    return m


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    grid = [list(line) for line in data.split('\n')]

    start = (1, 0)
    stop = (len(grid[0]) - 2, len(grid) - 1)

    points = [start, stop]

    for sr, row in enumerate(grid):
        for sc, ch in enumerate(row):
            if ch == '#':
                continue
            neighbors = 0
            for nc, nr in [(sc - 1, sr), (sc + 1, sr), (sc, sr - 1), (sc, sr + 1)]:
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc] != '#':
                    neighbors += 1
            if neighbors >= 3:
                points.append((sc, sr))

    graph = {pt: {} for pt in points}

    for sc, sr in points:
        stack = [(sc, sr, 0)]
        seen = {(sc, sr)}

        while stack:
            c, r, n = stack.pop()

            if n != 0 and (c, r) in points:
                graph[(sc, sr)][(c, r)] = n
                continue

            for dc, dr in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr = r + dr
                nc = c + dc
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and\
                        grid[nr][nc] != '#' and (nc, nr) not in seen:
                    stack.append((nc, nr, n + 1))
                    seen.add((nc, nr))

    print(dfs(start, graph, stop))

    return 0


if __name__ == '__main__':
    main()
