################################################
# File: Part2.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 2 for day 8 of AOC.               #
# Vers: 1.0.0 12/08/2023 CBW - Original code.  #
################################################
import sys
import math
import re


class node:
    left = ''
    right = ''
    name = ''

    def __init__(self, name, left, right):
        self.name = name
        self.left = left
        self.right = right


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    input = data.split('\n')[0]
    lines = data.split('\n')[2:]
    steps = 0
    nodes = []
    count = 0
    paths = []
    for line in lines:
        name, left, right = re.findall(r'(\w+) = \((\w+), (\w+)\)', line)[0]
        nodes.append(node(name, left, right))
        if name.endswith('A'):
            paths.append(count)
        count += 1

    memoize = {}
    done = False
    stops = [-1 for i in range(len(paths))]
    starts = stops.copy()
    while not done:
        dir = input[steps % len(input)]
        for i, path in enumerate(paths):
            checkNode = nodes[path]

            if checkNode.name + dir in memoize:
                paths[i] = memoize[checkNode.name + dir]
            else:
                for j, n in enumerate(nodes):
                    check = checkNode.left if dir == 'L' \
                        else checkNode.right
                    if n.name == check:
                        memoize[checkNode.name + dir] = j
                        paths[i] = j
                        break

        for i, path in enumerate(paths):
            if not nodes[path].name.endswith('Z'):
                continue

            if starts[i] == -1:
                starts[i] = steps
            elif stops[i] == -1:
                stops[i] = steps

        if all([el != -1 for el in starts]) and \
                all([el != -1 for el in stops]):
            done = True

        steps += 1

    paths = [stop - start for stop, start in zip(stops, starts)]

    print(math.lcm(*(path for path in paths)))

    return 0


if __name__ == '__main__':
    main()
