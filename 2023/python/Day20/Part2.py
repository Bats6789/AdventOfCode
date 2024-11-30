################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 20 of AOC.              #
# Vers: 1.0.0 12/20/2023 CBW - Original code.  #
################################################
import math
import sys
from collections import deque


class Module:
    def __init__(self, name, type, outputs):
        self.name = name
        self.type = type
        self.outputs = outputs

        if type == '%':
            self.memory = False
        else:
            self.memory = {}

    def __repr__(self):
        return self.name + f'{{{self.type=},outputs={", ".join(self.outputs)},{self.memory=}}}'


def parseInput(lines):
    modules = {}
    broadcast_targets = []
    for line in lines:
        input, outputs = line.split(' -> ')
        if input == 'broadcaster':
            broadcast_targets = outputs.split(', ')
        else:
            type = input[0]
            name = input[1:]
            modules[name] = Module(name, type, outputs.split(', '))

    return (modules, broadcast_targets)


def updateLinks(modules):
    for name, module in modules.items():
        for output in module.outputs:
            if output in modules and modules[output].type == '&':
                modules[output].memory[name] = False

    pass


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    lines = data.split('\n')

    modules, broadcast_targets = parseInput(lines)
    updateLinks(modules)

    (feed,) = [name for name, module in modules.items() if 'rx' in module.outputs]

    cycle_lengths = {}
    seen = {name: 0 for name, module in modules.items() if feed in module.outputs}

    presses = 0

    while True:
        presses += 1
        q = deque([("broadcaster", target, False) for target in broadcast_targets])

        while q:
            origin, target, pulse = q.popleft()

            if target not in modules:
                continue

            module = modules[target]

            if module.name == feed and pulse:
                seen[origin] += 1

                if origin not in cycle_lengths:
                    cycle_lengths[origin] = presses

                if all(seen.values()):
                    x = 1
                    for cycle_lengths in cycle_lengths.values():
                        x = math.lcm(x, cycle_lengths)
                    print(x)
                    exit(0)

            if module.type == '%' and not pulse:
                module.memory = not module.memory
                for output in module.outputs:
                    q.append((module.name, output, module.memory))
            elif module.type == '&':
                module.memory[origin] = pulse
                outgoing = not all(module.memory.values())
                for output in module.outputs:
                    q.append((module.name, output, outgoing))


if __name__ == '__main__':
    main()
