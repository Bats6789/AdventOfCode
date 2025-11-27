import sys
import heapq


class Point:
    def __init__(self, score=0, x=0, y=0):
        self.score = score
        self.x = x
        self.y = y

    def __lt__(self, other):
        return self.score < other.score

    def shift_right(self):
        return Point(self.score + 1, self.x + 1, self.y)

    def shift_left(self):
        return Point(self.score + 1, self.x - 1, self.y)

    def shift_down(self):
        return Point(self.score + 1, self.x, self.y + 1)

    def shift_up(self):
        return Point(self.score + 1, self.x, self.y - 1)


def valid(point):
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

    step = Point()
    q = []

    heapq.heappush(q, step)

    step = heapq.heappop(q)

    while step.x != width - 1 or step.y != height - 1:
        grid[step.y][step.x] = ('.', True)
        tmp = step.shift_left()
        if step.x > 0 and tmp not in q and valid(grid[tmp.y][tmp.x]):
            grid[tmp.y][tmp.x] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = step.shift_right()
        if step.x < width - 1 and tmp not in q and valid(grid[tmp.y][tmp.x]):
            grid[tmp.y][tmp.x] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = step.shift_up()
        if tmp.y > 0 and tmp not in q and valid(grid[tmp.y][tmp.x]):
            grid[tmp.y][tmp.x] = ('.', True)
            heapq.heappush(q, tmp)
        tmp = step.shift_down()
        if step.y < height - 1 and tmp not in q and valid(grid[tmp.y][tmp.x]):
            grid[tmp.y][tmp.x] = ('.', True)
            heapq.heappush(q, tmp)

        step = heapq.heappop(q)

    print(step.score)

    return 0


if __name__ == '__main__':
    main()
