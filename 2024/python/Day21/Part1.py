import sys
from collections import deque
from functools import cache
from itertools import product

num_keypad = [
    ["7", "8", "9"],
    ["4", "5", "6"],
    ["1", "2", "3"],
    [None, "0", "A"]
]

dir_keypad = [
    [None, "^", "A"],
    ["<", "v", ">"]
]


def compute_seqs(keypad):
    pos = {}
    for i, row in enumerate(keypad):
        for j, el in enumerate(row):
            if el is not None:
                pos[el] = (i, j)

    seqs = {}
    for src in pos:
        for tgt in pos:
            if src == tgt:
                seqs[(src, tgt)] = ["A"]
                continue

            possibilities = []
            q = deque([(pos[src], "")])
            optimal = float("inf")

            while q:
                (row, col), moves = q.popleft()
                for nr, nc, nm in [(row - 1, col, "^"), (row + 1, col, 'v'), (row, col - 1, "<"), (row, col + 1, ">")]:
                    if nr < 0 or nc < 0 or nr >= len(keypad) or nc >= len(keypad[0]):
                        continue
                    if keypad[nr][nc] is None:
                        continue
                    if keypad[nr][nc] == tgt:
                        if optimal < len(moves) + 1:
                            break
                        optimal = len(moves) + 1
                        possibilities.append(moves + nm + "A")
                    else:
                        q.append(((nr, nc), moves + nm))
                else:
                    continue
                break
            seqs[(src, tgt)] = possibilities
    return seqs


num_seqs = compute_seqs(num_keypad)
dir_seqs = compute_seqs(dir_keypad)
dir_lengths = {key: len(value[0]) for key, value in dir_seqs.items()}


def solve(string, seqs):
    options = [seqs[(src, tgt)] for src, tgt in zip("A" + string, string)]
    return list("".join(opt) for opt in product(*options))


@cache
def compute_length(seq, depth=2):
    if depth == 1:
        return sum(dir_lengths[(src, tgt)] for src, tgt in zip("A" + seq, seq))

    length = 0
    for src, tgt in zip("A" + seq, seq):
        length += min(compute_length(subseq, depth - 1) for subseq in dir_seqs[(src, tgt)])

    return length


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0
    for line in data.split('\n'):
        total += min(map(compute_length, solve(line, num_seqs))) * int(line[:-1])

    print(total)

    return 0


if __name__ == '__main__':
    main()
