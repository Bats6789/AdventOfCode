import sys


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    total = 0

    ranges, _ = data.split('\n\n')
    ranges = list((list(map(int, spread.split('-'))) for spread in ranges.split('\n')))
    compressed_ranges = []

    for spread in ranges:
        did_compress = True
        while did_compress:
            did_compress = False
            for i, check in enumerate(compressed_ranges):
                if (spread[0] <= check[0] <= spread[1] or spread[0] <= check[1] <= spread[1] or
                    check[0] <= spread[0] <= check[1] or check[0] <= spread[1] <= check[1]):
                    spread[0] = min(check[0], spread[0])
                    spread[1] = max(check[1], spread[1])
                    compressed_ranges.pop(i)
                    did_compress = True
                    break

            if not did_compress:
                compressed_ranges.append(spread)

    for spread in compressed_ranges:
        total += spread[1] - spread[0] + 1

    print(total)
    return 0


if __name__ == '__main__':
    main()
