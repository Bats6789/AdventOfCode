import sys
import re


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    lines = data.split('\n')

    a_vals = list(map(int, re.split(r'\s+', lines[0])))
    v_vals = list(map(int, re.split(r'\s+', lines[1])))
    c_vals = list(map(int, re.split(r'\s+', lines[2])))
    d_vals = list(map(int, re.split(r'\s+', lines[3])))
    ops = re.split(r'\s+', lines[4])

    total = 0

    for (a, b, c, d, op) in zip(a_vals, v_vals, c_vals, d_vals, ops):
        if op == '+':
            total += a + b + c + d
        else:
            total += a * b * c * d

    print(total)
    return 0


if __name__ == '__main__':
    main()
