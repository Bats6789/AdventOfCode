import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    number = 50
    count = 0

    for line in data.split('\n'):
        c = line[0]
        num = int(line[1:])

        if num >= 100:
            count += num // 100
            num %= 100

        if c == 'L':
            if num > number:
                if number != 0:
                    count += 1
                number -= num
                number += 100
            else:
                number -= num
        else:
            number += num
            if number > 100:
                count += 1
            number %= 100

        if number == 0:
            count += 1

    print(count)
    return 0


if __name__ == '__main__':
    main()
