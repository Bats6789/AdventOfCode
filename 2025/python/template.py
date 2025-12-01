import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    print(data)
    return 0


if __name__ == '__main__':
    main()
