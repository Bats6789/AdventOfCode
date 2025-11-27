import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    validCount = 0
    for line in data.split('\n'):
        indexes, char, password = line.split(' ')
        indexes = list(int(val) for val in indexes.split('-'))
        char = char[0]
        if (password[indexes[0] - 1] == char) != (password[indexes[1] - 1] == char):
            validCount += 1

    print(validCount)

    return 0


if __name__ == '__main__':
    main()
