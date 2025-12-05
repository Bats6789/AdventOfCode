import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    ranges, ids = data.split('\n\n')
    ranges = list((tuple(map(int, spread.split('-'))) for spread in ranges.split('\n')))
    ids = list(map(int, ids.split('\n')))

    for id in ids:
        for spread in ranges:
            if spread[0] <= id <= spread[1]:
                total += 1
                break

    print(total)
    return 0


if __name__ == '__main__':
    main()
