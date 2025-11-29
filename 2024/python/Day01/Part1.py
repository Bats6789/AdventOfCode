import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    left = []
    right = []

    for line in data.split('\n'):
        l, r = line.split(' ')[0], line.split(' ')[-1]
        left.append(l)
        right.append(r)

    left = sorted(left)
    right = sorted(right)

    dist = 0
    for l, r in zip(left, right):
        dist += abs(int(l) - int(r))

    print(dist)
    return 0


if __name__ == '__main__':
    main()
