import sys


def isInvalid(val):
    valStr = str(val)
    length = len(valStr) // 2

    return valStr[:length] == valStr[length:]


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    for idRange in data.split(','):
        idRange = list(map(int, idRange.split('-')))

        for i in range(idRange[0], idRange[1] + 1):
            if isInvalid(i):
                total += i

    print(total)
    return 0


if __name__ == '__main__':
    main()
