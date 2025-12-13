import sys


def get_area(present):
    area = 0

    for row in present:
        for el in row:
            if el == '#':
                area += 1

    return area


def simple_presents_fit(width, height, presents, packages):
    area = width * height

    total_area = sum(package * get_area(present) for present, package in zip(presents, packages))

    if area >= total_area:
        return True


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    count = 0

    presents = []
    for chunk in data.split('\n\n'):
        if chunk[1] == ':':
            presents.append(list(list(line) for line in chunk.split('\n')[1:]))
        else:
            trees = chunk

    for tree in trees.split('\n'):
        size, packages = tree.split(': ')
        width, height = map(int, size.split('x'))
        packages = list(map(int, packages.split()))

        if simple_presents_fit(width, height, presents, packages):
            count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
