import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    numbers = list(map(int, data.split('\n')))

    answer = 0
    for i, num in enumerate(numbers[:-2]):
        for j, num2 in enumerate(numbers[i + 1:-1]):
            for k, num3 in enumerate(numbers[i + 1:-1]):
                if num + num2 + num3 == 2020:
                    answer = num * num2 * num3
                    break
            if answer != 0:
                break
        if answer != 0:
            break

    print(answer)
    return 0


if __name__ == '__main__':
    main()
