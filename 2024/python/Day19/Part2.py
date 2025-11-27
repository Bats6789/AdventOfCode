import sys

d = {}

def valid(towels, desire):
    if desire in d:
        return d[desire]

    if len(desire) == 0:
        d[desire] = 1
        return 1

    d[desire] = 0

    for towel in towels:
        if towel == desire[:len(towel)]:
            d[desire] += valid(towels, desire[len(towel):])

    return d[desire]


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    towels, desired = data.split('\n\n')

    towels = towels.split(', ')

    count = 0
    for desire in desired.split('\n'):
        count += valid(towels, desire)

    print(count)

    return 0


if __name__ == '__main__':
    main()
