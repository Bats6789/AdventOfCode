import sys
import networkx as nx


def parseNode(nodeStr):
    weight, id = nodeStr.split(' ', 1)
    weight = int(weight)
    id = id.replace('bags', '').replace('bag', '').strip()

    # print(weight, id)

    return weight, id


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    g = nx.DiGraph()

    for line in data.split('\n'):
        source, targets = line.split('contain')
        source = source.replace('bags', '').strip()
        targets = targets.strip()

        if 'no' in targets:
            pass
        elif ',' in targets:
            for target in targets.split(', '):
                if '.' in target:
                    weight, target = parseNode(target[:-1])
                else:
                    weight, target = parseNode(target)
                g.add_edge(source, target, weight=weight)
        else:
            weight, target = parseNode(targets[:-1])
            g.add_edge(source, target, weight=weight)

    q = []
    total = 0

    for node, vals in g['shiny gold'].items():
        weight = vals['weight']
        total += weight
        for _ in range(weight):
            q.insert(0, node)

    while len(q) > 0:
        node = q.pop()

        for item, vals in g[node].items():
            weight = vals['weight']
            total += weight
            for _ in range(weight):
                q.insert(0, item)

    print(total)

    return 0


if __name__ == '__main__':
    main()
