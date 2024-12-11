import sys


dp = {}


def get_stones(item, step):
    key = (item, step)
    if key in dp:
        return dp[key]

    tmp = str(item)
    if step == 0:
        ret = 1
    elif item == 0:
        ret = get_stones(1, step - 1)
    elif len(tmp) % 2 == 0:
        left = int(tmp[:len(tmp) // 2])
        right = int(tmp[len(tmp) // 2:])
        ret = get_stones(left, step - 1) + get_stones(right, step - 1)
    else:
        ret = get_stones(item * 2024, step - 1)

    dp[key] = ret

    return ret


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    items = list(map(int, data.split(' ')))

    count = 0

    for item in items:
        count += get_stones(item, 75)

    print(count)

    return 0


if __name__ == '__main__':
    main()
