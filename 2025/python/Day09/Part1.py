import sys
from itertools import combinations


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


    def __str__(self):
        return f"{self.x},{self.y}"


    def from_str(str):
        x, y = tuple(map(int, str.split(',')))
        return Point(x, y)


    def area(self, target: Point):
        return (abs(self.x - target.x) + 1) * (abs(self.y - target.y) + 1)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    points = [Point.from_str(line) for line in data.split('\n')]

    print(max(p1.area(p2) for p1, p2 in combinations(points, 2)))
    return 0


if __name__ == '__main__':
    main()
