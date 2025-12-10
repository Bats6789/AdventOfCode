import sys
from collections import deque


def parse_button(str):
    return tuple(int(el) for el in str[1:-1].split(','))


def update(state, button):
    new_state = state.copy()
    for item in button:
        new_state[item] = not state[item]

    return new_state

def get_min_presses(target, buttons):
    state = [False] * len(target)

    seen = set()

    q = deque()

    if state == target:
        return 0

    seen.add(''.join('#' if el else '.' for el in state))

    for button in buttons:
        new_state = update(state, button)
        if new_state == target:
            return 1

        str_state = ''.join('#' if el else '.' for el in new_state)
        if str_state not in seen:
            seen.add(str_state)
            q.append((new_state, 1))

    while q:
        state, button_history = q.popleft()

        for button in buttons:
            new_state = update(state, button)
            if new_state == target:
                return button_history + 1
            
            str_state = ''.join('#' if el else '.' for el in new_state)
            if str_state not in seen:
                seen.add(str_state)
                q.append((new_state, button_history + 1))

    return 0


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    total = 0

    for line in data.split('\n'):
        target = list(True if c == '#' else False for c in line[1:line.index(']')].strip())
        buttons = list(parse_button(el) for el in line[line.index(']') + 2:line.index('{')].strip().split(' '))

        total += get_min_presses(target, buttons)
        
    print(total)

    return 0


if __name__ == '__main__':
    main()
