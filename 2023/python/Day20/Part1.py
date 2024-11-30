################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 20 of AOC.              #
# Vers: 1.0.0 12/20/2023 CBW - Original code.  #
################################################
import sys
from collections import deque


class Module:
    def __init__(self, name, type, outputs):
        self.name = name
        self.type = type
        self.outputs = outputs

        if type == '%':
            self.memory = "off"
        else:
            self.memory = {}

    def __repr__(self):
        return self.name + f'{{{self.type=},outputs={", ".join(self.outputs)},{self.memory=}}}'


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')
    modules = {}
    broadcast_targets = []
    for line in lines:
        input, outputs = line.split(' -> ')
        # print(input, outputs)
        if input == 'broadcaster':
            broadcast_targets = outputs.split(', ')
        else:
            type = input[0]
            name = input[1:]
            modules[name] = Module(name, type, outputs.split(', '))

    for name, module in modules.items():
        for output in module.outputs:
            if output in modules and modules[output].type == '&':
                modules[output].memory[name] = 'lo'

    lo = hi = 0
    for _ in range(1000):
        lo += 1
        q = deque([("broadcaster", target, "lo") for target in broadcast_targets])

        while q:
            origin, target, pulse = q.popleft()

            if pulse == 'lo':
                lo += 1
            else:
                hi += 1

            if target not in modules:
                continue

            module = modules[target]

            if module.type == '%':
                if pulse == 'lo':
                    module.memory = 'lo' if module.memory == 'hi' else 'hi'
                    for output in module.outputs:
                        q.append((module.name, output, module.memory))
            else:
                module.memory[origin] = pulse
                outgoing = 'lo' if all(x == 'hi' for x in module.memory.values()) else 'hi'
                for output in module.outputs:
                    q.append((module.name, output, outgoing))

    print(lo * hi)


if __name__ == '__main__':
    main()
