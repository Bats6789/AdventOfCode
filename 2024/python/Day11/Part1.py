import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    items = list(map(int, data.split(' ')))

    for i in range(25):
        new_items = []
        for item in items:
            tmp = str(item)
            if item == 0:
                new_items.append(1)
            elif len(tmp) % 2 == 0:
                new_items.append(int(tmp[:len(tmp) // 2]))
                new_items.append(int(tmp[len(tmp) // 2:]))
            else:
                new_items.append(2024 * item)

        items = new_items

    print(len(items))
    return 0


if __name__ == '__main__':
    main()
