import sys
from itertools import combinations


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def from_str(str):
        x, y = tuple(map(int, str.split(',')))
        return Point(x, y)

    def area(self, target):
        return (abs(self.x - target.x) + 1) * (abs(self.y - target.y) + 1)


def on_vertical_line(points, x, y):
    checks = [p for p in points if p.x == x]
    if checks == []:
        return False

    p1, p2 = checks

    if p1.y > p2.y:
        p1, p2 = p2, p1

    return p1.y <= y <= p2.y


def on_horizontal_line(points, x, y):
    checks = [p for p in points if p.y == y]
    if checks == []:
        return False

    p1, p2 = checks

    if p1.x > p2.x:
        p1, p2 = p2, p1

    return p1.x <= x <= p2.x


def get_vertical_edge(points, x):
    y1, y2 = [p.y for p in points if p.x == x]

    edge_start = min(y1, y2)
    edge_stop = max(y1, y2)

    return edge_start, edge_stop


def get_horizontal_edge(points, y):
    x1, x2 = [p.x for p in points if p.y == y]

    edge_start = min(x1, x2)
    edge_stop = max(x1, x2)

    return edge_start, edge_stop


def rectangle_is_inside(points, split_points, targets):
    p1, p2 = targets

    xs, ys = split_points

    if p1.x < p2.x:
        left_x = p1.x
        right_x = p2.x
    else:
        left_x = p2.x
        right_x = p1.x

    if p1.y < p2.y:
        top_y = p1.y
        bottom_y = p2.y
    else:
        top_y = p2.y
        bottom_y = p1.y

    for x in xs:
        if left_x < x < right_x:
            edge_start, edge_stop = get_vertical_edge(points, x)
            intersect_start = max(edge_start, top_y)
            intersect_stop = min(edge_stop, bottom_y)

            if intersect_start < intersect_stop:
                return False

    for y in ys:
        if top_y < y < bottom_y:
            edge_start, edge_stop = get_horizontal_edge(points, y)
            intersect_start = max(edge_start, left_x)
            intersect_stop = min(edge_stop, right_x)

            if intersect_start < intersect_stop:
                return False

    center_x = (left_x + right_x) / 2
    center_y = (top_y + bottom_y) / 2
    inside = False

    for i in range(len(points)):
        vertex1 = points[i]
        if i == len(points) - 1:
            vertex2 = points[0]
        else:
            vertex2 = points[i + 1]

        x1, y1 = float(vertex1.x), float(vertex1.y)
        x2, y2 = float(vertex2.x), float(vertex2.y)

        if (y1 > center_y) != (y2 > center_y):
            intersect_x = (x2 - x1) * (center_x - y1) / (y2 - y1) + x1

            if center_x < intersect_x:
                inside = not inside

    return inside


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    points = [Point.from_str(line) for line in data.split('\n')]

    max_area = 0

    xs = sorted(list({p.x for p in points}))
    ys = sorted(list({p.y for p in points}))
    split_points = (xs, ys)

    for p1, p2 in combinations(points, 2):
        if p1.area(p2) <= max_area:
            continue  # skip areas that could never be larger

        if p1.x == p2.x or p1.y == p2.y:
            max_area = max(max_area, p1.area(p2))
            continue

        if rectangle_is_inside(points, split_points, (p1, p2)):
            max_area = max(max_area, p1.area(p2))

    print(max_area)

    return 0


if __name__ == '__main__':
    main()
