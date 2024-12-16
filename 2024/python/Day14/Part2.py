import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    robots = []

    for line in data.split('\n'):
        p, v = line.split(' ')
        p = p.split('=')[1]
        v = v.split('=')[1]

        p = list(map(int, p.split(',')))
        v = list(map(int, v.split(',')))

        robots.append((p, v))

    height = 103
    width = 101
    for _ in range(100):
        for i, robot in enumerate(robots):
            p, v = robot
            p[0] += v[0]
            p[1] += v[1]
            if p[0] < 0:
                p[0] = width + p[0]
            elif p[0] >= width:
                p[0] = p[0] - width
            if p[1] < 0:
                p[1] = height + p[1]
            elif p[1] >= height:
                p[1] = p[1] - height

    tl = 0
    tr = 0
    bl = 0
    br = 0
    for robot in robots:
        p, _ = robot
        if p[0] < width // 2:
            if p[1] < height // 2:
                tl += 1
            elif p[1] > height // 2:
                bl += 1
        elif p[0] > width // 2:
            if p[1] < height // 2:
                tr += 1
            elif p[1] > height // 2:
                br += 1

    # print(tl, tr, bl, br)
    print(tl * tr * bl * br)
    return 0


if __name__ == '__main__':
    main()
