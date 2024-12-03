import sys
import re


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    results = re.findall(r"do\(\)|don't\(\)|mul\(\d+,\d+\)", data)
    total = 0
    do_it = True
    for ans in results:
        if ans[0] == 'm' and do_it:
            left, right = ans.split(',')
            left = int(left[4:])
            right = int(right[:-1])
            total += left * right
        elif ans[0] == 'd':
            do_it = ans == 'do()'
    print(total)
    return 0


if __name__ == '__main__':
    main()
