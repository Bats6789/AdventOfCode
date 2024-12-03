import sys
import re


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    results = re.findall(r"mul\(\d+,\d+\)", data)
    total = 0
    for ans in results:
        left, right = ans.split(',')
        left = int(left[4:])
        right = int(right[:-1])
        total += left * right
    print(total)
    return 0


if __name__ == '__main__':
    main()
