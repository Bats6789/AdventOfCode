import sys


def get_prices(val):
    prune_val = 16777216

    price = val % 10

    prices = [price]

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

        price = val % 10

        prices.append(price)

    return prices


def get_sells(prices, changes):
    sells = {}

    for i in range(len(changes) - 3):
        seq = tuple(changes[i + j] for j in range(4))
        if seq not in sells:
            sells[seq] = prices[i + 4]

    return sells


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    bananas = {}
    for line in data.split('\n'):
        val = int(line)

        prices = get_prices(val)
        changes = [new - prev for prev, new in zip(prices[:-1], prices[1:])]
        sells = get_sells(prices, changes)
        for seq, price in sells.items():
            if seq not in bananas:
                bananas[seq] = price
            else:
                bananas[seq] += price

    max_bananas = max(bananas.values())
    print(max_bananas)

    return 0


if __name__ == '__main__':
    main()
