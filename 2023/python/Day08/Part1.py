################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 8 of AOC.               #
# Vers: 1.0.0 12/08/2023 CBW - Original code.  #
################################################
import sys
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
    index = 0
    for line in lines:
        name, left, right = re.findall(r'(\w+) = \((\w+), (\w+)\)', line)[0]
        nodes.append(node(name, left, right))
        if name == 'AAA':
            index = count
        count += 1

    name = 'AAA'
    memoize = {}
    while name != 'ZZZ':
        dir = input[steps % len(input)]
        if name + dir in memoize:
            index, name = memoize[name + dir]
        else:
            for i, n in enumerate(nodes):
                check = nodes[index].left if dir == 'L' else nodes[index].right
                if n.name == check:
                    memoize[name + dir] = (i, n.name)
                    index = i
                    name = n.name
                    break
        steps += 1

    print(steps)
    return 0


if __name__ == '__main__':
    main()
