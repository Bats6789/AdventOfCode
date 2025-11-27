import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    validCount = 0
    for line in data.split('\n'):
        spread, char, password = line.split(' ')
        spread = list(int(val) for val in spread.split('-'))
        char = char[0]
        count = password.count(char)
        if count >= spread[0] and count <= spread[1]:
            validCount += 1

    print(validCount)

    return 0


if __name__ == '__main__':
    main()
