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


def isvalid_list(items, order):
    seen = {}

    for item in items:
        item = int(item)

        if item in order:
            for check in order[item]:
                if check in seen:
                    return False

        seen[item] = True

    return True


def fix_list(line, order):
    itemized = list(map(int, line.split(',')))

    while not isvalid_list(itemized, order):
        seen = {}
        skip = False
        for i, item in enumerate(itemized):
            if item in order:
                for check in order[item]:
                    if check in seen:
                        check_i = itemized.index(check)
                        itemized[i], itemized[check_i] = check, item
                        skip = True
                        break
                if skip:
                    break

            seen[item] = True

    return ",".join(str(item) for item in itemized)


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

    invalid = []

    for line in updates.split('\n'):
        if not isvalid(line, before):
            invalid.append(line)

    valid = []
    valid = list(map(lambda line: fix_list(line, before), invalid))
    total = 0
    for line in valid:
        items = list(map(int, line.split(',')))

        total += items[len(items) // 2]

    print(total)

    return 0


if __name__ == '__main__':
    main()
