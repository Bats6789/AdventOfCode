import sys
from collections import deque
from scipy.optimize import linprog


def parse_button(str):
    return tuple(int(el) for el in str[1:-1].split(','))

def parse_joltage(str):
    return tuple(int(el) for el in str[1:-1].split(','))


def update(state, button):
    new_state = state.copy()
    for item in button:
        new_state[item] += 1

    return new_state

def get_min_presses(target, buttons):
    state = [0] * len(target)

    seen = set()

    q = deque()

    if state == target:
        return 0

    seen.add(','.join(map(str, state)))

    for button in buttons:
        new_state = update(state, button)
        if new_state == target:
            return 1

        str_state = ','.join(map(str, new_state))
        if str_state not in seen:
            seen.add(str_state)
            q.append((new_state, 1))

    while q:
        state, button_history = q.popleft()

        for button in buttons:
            new_state = update(state, button)

            if any(n > t for n, t in zip(new_state, target)):
                continue

            str_state = ','.join(map(str, new_state))
            if str_state not in seen:
                seen.add(str_state)
                q.append((new_state, button_history + 1))
            else:
                continue

            if new_state == target:
                return button_history + 1

            

    return 0


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0

    total_lines = len(data.split('\n'))

    for i, line in enumerate(data.split('\n')):
        # target = list(True if c == '#' else False for c in line[1:line.index(']')].strip())
        buttons = list(parse_button(el) for el in line[line.index(']') + 2:line.index('{')].strip().split(' '))
        target = parse_joltage(line[line.index('{'):line.index('}') + 1].strip())
        costs = [1] * len(buttons)
        buttons = [[(i in b) for b in buttons] for i in range(len(target))]

        # total += get_min_presses(target, buttons)
        # print(f"{i + 1}/{total_length}")
        total += linprog(costs, A_eq=buttons, b_eq=target, integrality=1).fun
        
    print(int(total))

    return 0


if __name__ == '__main__':
    main()
