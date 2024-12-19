import sys

d = {}

def valid(towels, desire):
    if desire in d:
        return d[desire]

    if len(desire) == 0:
        d[desire] = True
        return True

    for towel in towels:
        if towel == desire[:len(towel)] and valid(towels, desire[len(towel):]):
            d[desire] = True
            return True

    d[desire] = False
    return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    towels, desired = data.split('\n\n')

    towels = towels.split(', ')

    count = 0
    for desire in desired.split('\n'):
        if valid(towels, desire):
            count += 1

    print(count)

    return 0


if __name__ == '__main__':
    main()
