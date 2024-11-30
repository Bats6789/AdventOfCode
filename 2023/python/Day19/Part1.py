################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 19 of AOC.              #
# Vers: 1.0.0 12/19/2023 CBW - Original code.  #
################################################
import sys


class Part:
    def __init__(self, x, m, a, s):
        self.x = x
        self.m = m
        self.a = a
        self.s = s
        pass

    def score(self):
        return self.x + self.m + self.a + self.s


class Ops:
    def __init__(self, param, cmp, value, result):
        self.param = param
        self.cmp = cmp
        self.value = value
        self.result = result
        pass

    def validate(self, part: Part):
        match(self.param):
            case 'x':
                paramValue = part.x
            case 'm':
                paramValue = part.m
            case 'a':
                paramValue = part.a
            case 's':
                paramValue = part.s

        if self.cmp == '>':
            return paramValue > self.value
        else:
            return paramValue < self.value


def validate(rules, part):
    result = 'in'

    while result != 'A' and result != 'R':
        rule = rules[result]
        for op in rule:
            if op.param == '':
                result = op.result
            else:
                if op.validate(part):
                    result = op.result
                    break

    return result == 'A'


def parseRules(rules):
    newRules = {}
    for rule in rules.split('\n'):
        name, ops = rule.split('{')  # }
        ops = ops[:-1]
        newOps = []
        for op in ops.split(','):
            if op.count(':') > 0:
                left, result = op.split(':')
                param = left[0]
                cmp = left[1]
                value = int(left[2:])
                newOps.append(Ops(param, cmp, value, result))
            else:
                result = op
                newOps.append(Ops('', '', 0, result))
        newRules[name] = newOps

    return newRules


def parseParts(parts):
    newParts = []
    for line in parts.split('\n'):
        line = line[1:-1]
        x, m, a, s = line.split(',')
        x = int(x.split('=')[1])
        m = int(m.split('=')[1])
        a = int(a.split('=')[1])
        s = int(s.split('=')[1])
        newParts.append(Part(x, m, a, s))

    return newParts


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()
    rules, parts = data.split('\n\n')

    rules = parseRules(rules)
    parts = parseParts(parts)

    score = 0
    for part in parts:
        if validate(rules, part):
            score += part.score()

    print(score)
    return 0


if __name__ == '__main__':
    main()
