import sys


def isvalid(line, order):
    seen = {}

    for item in line.split(','):
        item = int(item)

        if item in order:
            for check in order[item]:
                if check in seen:
                    return False

        seen[item] = True
    return True


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    order, updates = data.split('\n\n')

    before = {}

    for o in order.split('\n'):
        left, right = o.split('|')
        left = int(left)
        right = int(right)

        if left not in before:
            before[left] = [right]
        else:
            before[left].append(right)

    valid = []

    for line in updates.split('\n'):
        if isvalid(line, before):
            valid.append(line)

    total = 0
    for line in valid:
        items = list(map(int, line.split(',')))

        total += items[len(items) // 2]

    print(total)

    return 0


if __name__ == '__main__':
    main()
