import sys


def passing(test, values):
    new_vals = []

    if len(values) == 1:
        return test == values[0]

    new_vals.append(values[0] + values[1])
    if len(values) > 2:
        for value in values[2:]:
            new_vals.append(value)

    if passing(test, new_vals):
        return True

    new_vals = []
    new_vals.append(values[0] * values[1])
    if len(values) > 2:
        for value in values[2:]:
            new_vals.append(value)

    if passing(test, new_vals):
        return True

    return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0

    for line in data.split('\n'):
        test, values = line.split(': ')
        test = int(test)
        values = list(map(int, values.split(' ')))

        if passing(test, values):
            total += test

    print(total)
    return 0


if __name__ == '__main__':
    main()
