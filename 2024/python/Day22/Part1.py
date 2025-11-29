import sys


def secret(val):
    prune_val = 16777216

    for _ in range(2000):
        tmp = val * 64
        val ^= tmp
        val %= prune_val

        tmp = val // 32
        val ^= tmp
        val %= prune_val

        tmp = val * 2048
        val ^= tmp
        val %= prune_val

    return val

def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    for line in data.split('\n'):
        val = int(line)

        total += secret(val)

    print(total)
    return 0


if __name__ == '__main__':
    main()
