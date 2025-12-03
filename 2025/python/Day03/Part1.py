import sys


def getMaxJolt(line):
    maxVal = 0
    for i in range(len(line) - 1):
        for j in range(i + 1, len(line)):
            maxVal = max(maxVal, int(line[i] + line[j]))

    return maxVal


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    for line in data.split('\n'):
        total += getMaxJolt(line)

    print(total)
    return 0


if __name__ == '__main__':
    main()
