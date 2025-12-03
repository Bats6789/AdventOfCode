import sys


def getMaxJolt(line):
    indexes = list(range(len(line) - 12, len(line)))

    for i in range(12):
        for j in range(0 if i == 0 else indexes[i - 1] + 1, indexes[i]):
            if line[j] > line[indexes[i]] or (line[j] == line[indexes[i]] and j < indexes[i]):
                indexes[i] = j

    strVal = ""
    for index in indexes:
        strVal += line[index]

    return int(strVal)


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    for line in data.split('\n'):
        val = getMaxJolt(line)
        total += val

    print(total)
    return 0


if __name__ == '__main__':
    main()
