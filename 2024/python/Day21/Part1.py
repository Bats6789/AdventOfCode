import sys


mapping = {
    '7': (0, 0),
    '8': (1, 0),
    '9': (2, 0),
    '4': (0, 1),
    '5': (1, 1),
    '6': (2, 1),
    '1': (0, 2),
    '2': (1, 2),
    '3': (2, 2),
    '0': (1, 3),
    'A': (2, 3)
}

second_mapping = {
    'A': (2, 0),
    '^': (1, 0),
    '<': (0, 1),
    'v': (1, 1),
    '>': (2, 1)
}


def get_sequence(s):
    seq = []

    loc = mapping['A']

    for el in s:
        obj = mapping[el]

        if loc[1] == 3 and obj[0] == 0:
            seq += '^'
            loc = (loc[0], 2)

        if loc[0] == 0 and obj[1] == 3:
            seq += '>'
            loc = (1, loc[1])

        if seq != [] and seq[len(seq) - 1] in ['<', '>', 'A']:
            for _ in range(abs(obj[0] - loc[0])):
                seq += '<' if obj[0] < loc[0] else '>'
            for _ in range(abs(obj[1] - loc[1])):
                seq += '^' if obj[1] < loc[1] else 'v'
        else:
            for _ in range(abs(obj[1] - loc[1])):
                seq += '^' if obj[1] < loc[1] else 'v'
            for _ in range(abs(obj[0] - loc[0])):
                seq += '<' if obj[0] < loc[0] else '>'

        seq += 'A'
        loc = obj

    return seq


def get_sequence2(s):
    seq = []

    loc = second_mapping['A']

    for el in s:
        obj = second_mapping[el]

        if obj[0] == 0 and loc[1] == 0:
            seq += 'v'
            loc = (loc[0], 1)

        if obj[1] == 0 and loc[0] == 0:
            seq += '>'
            loc = (1, loc[1])

        if seq != [] and seq[len(seq) - 1] in ['<', '>', 'A']:
            for _ in range(abs(obj[0] - loc[0])):
                seq += '<' if obj[0] < loc[0] else '>'
            for _ in range(abs(obj[1] - loc[1])):
                seq += '^' if obj[1] < loc[1] else 'v'
        else:
            for _ in range(abs(obj[1] - loc[1])):
                seq += '^' if obj[1] < loc[1] else 'v'
            for _ in range(abs(obj[0] - loc[0])):
                seq += '<' if obj[0] < loc[0] else '>'

        seq += 'A'
        loc = obj

    return seq


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    for line in data.split('\n'):
        num = int(line[:-1])
        # print(f"{num}, {line}")

        seq = get_sequence(line)
        seq2 = get_sequence2(seq)
        seq3 = get_sequence2(seq2)
        # print("".join(seq))
        # print("".join(seq2))
        # print("".join(seq3))
        l = len(seq3)
        # print(f"{num}, {l}")

        total += num * l
    print(total)
    return 0


if __name__ == '__main__':
    main()
