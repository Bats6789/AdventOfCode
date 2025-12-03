import sys


def isPalindrome(val):
    valStr = str(val)
    length = len(valStr) // 2

    for i in range(1, length + 1):
        if len(valStr) % i != 0:
            continue
        match = True
        for j in range(1, len(valStr) // i):
            # print(f"{valStr[i * (j - 1):i * j]} == {valStr[i * j:i * (j + 1)]}")
            if valStr[i * (j - 1):i * j] != valStr[i * j:i * (j + 1)]:
                match = False
                break
        if match:
            return True

    return False


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    for idRange in data.split(','):
        idRange = list(map(int, idRange.split('-')))
        # print(idRange)

        for i in range(idRange[0], idRange[1] + 1):
            if isPalindrome(i):
                # print(i, end=' ')
                total += i
        # print()

    print(total)
    return 0


if __name__ == '__main__':
    main()
