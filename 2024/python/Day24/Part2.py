import sys


def eval(left, right, op, gates, ops):
    # print(left, right, op)
    if left in gates:
        left_val = gates[left]
    else:
        for key, res in ops.items():
            if res == left:
                l, r, op2 = key
        left_val = eval(l, r, op2, gates, ops)

    if right in gates:
        right_val = gates[right]
    else:
        for key, res in ops.items():
            if res == right:
                l, r, op2 = key
        right_val = eval(l, r, op2, gates, ops)

    match(op):
        case 'XOR':
            # print(f"{left_val} ^ {right_val} = {left_val ^ right_val}")
            return left_val ^ right_val
        case 'AND':
            # print(f"{left_val} & {right_val} = {left_val & right_val}")
            return left_val & right_val
        case 'OR':
            # print(f"{left_val} | {right_val} = {left_val | right_val}")
            return left_val | right_val


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    starting, logic = data.split('\n\n')

    gates = dict()
    for val in starting.split('\n'):
        gate, state = val.split(': ')
        gates[gate] = int(state)

    ops = dict()
    for val in logic.split('\n'):
        left, right = val.split(' -> ')

        l, op, r = left.split(' ')
        ops[(l, r, op)] = right

    results = dict()
    for line, res in ops.items():
        l, r, op = line

        if res[0] == 'z':
            results[res] = eval(l, r, op, gates, ops)

    results_keys = sorted(results.keys(), reverse=True)

    ans = 0
    for res in results_keys:
        # print(res)
        ans <<= 1
        ans = ans | results[res]
    print(ans)
    return 0


if __name__ == '__main__':
    main()
