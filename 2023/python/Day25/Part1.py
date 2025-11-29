################################################
# File: Part1.py                               #
# Auth: Blake Wingard - bats23456789@gmail.com #
# Desc: Part 1 for day 25 of AOC.              #
# Vers: 1.0.0 12/25/2023 CBW - Original code.  #
################################################
import sys
import networkx as nx


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    g = nx.Graph()

    for line in data.split('\n'):
        left, right = line.split(':')
        for node in right.strip().split():
            g.add_edge(left, node)

    g.remove_edges_from(nx.minimum_edge_cut(g))
    a, b = nx.connected_components(g)

    print(len(a) * len(b))

    return 0


if __name__ == '__main__':
    main()
