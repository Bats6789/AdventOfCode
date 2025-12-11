import sys
import networkx as nx


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    dg = nx.DiGraph()

    for line in data.split('\n'):
        src, targets = line.split(': ')

        targets = targets.split()

        for target in targets:
            dg.add_edge(src, target)

    paths = nx.all_simple_paths(dg, "you", "out")

    print(len(list(paths)))
    return 0


if __name__ == '__main__':
    main()
