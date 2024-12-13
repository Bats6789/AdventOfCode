import sys


sys.setrecursionlimit(10**7)


dp = {}


def get_wins(prize, a, b):
    if prize in dp:
        return dp[prize]

    if prize[0] == 0 and prize[1] == 0:
        return 0

    if prize[0] < 0 or prize[1] < 0:
        return 10**10

    a_val = 3 + get_wins((prize[0] - a[0], prize[1] - a[1]), a, b)
    b_val = 1 + get_wins((prize[0] - b[0], prize[1] - b[1]), a, b)
    ans = min(a_val, b_val)

    dp[prize] = ans
    return ans


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    games = data.split('\n\n')

    total = 0

    for game in games:
        a, b, prize = game.split('\n')
        a = a.split(': ')[1]
        left, right = a.split(', ')
        left = int(left[2:])
        right = int(right[2:])
        a = (left, right)
        b = b.split(': ')[1]
        left, right = b.split(', ')
        left = int(left[2:])
        right = int(right[2:])
        b = (left, right)
        prize = prize.split(': ')[1]
        left, right = prize.split(', ')
        left = int(left[2:])
        right = int(right[2:])
        prize = (left, right)
        global dp
        dp = {}
        ans = get_wins(prize, a, b)
        if ans < 10**9:
            total += ans

    print(total)
    return 0


if __name__ == '__main__':
    main()
