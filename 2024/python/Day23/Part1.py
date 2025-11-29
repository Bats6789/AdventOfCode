import sys
import networkx as nx


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    G = nx.Graph()

    for line in data.split('\n'):
        left, right = line.split('-')
        G.add_edge(left, right)

    count = 0
    for check in nx.enumerate_all_cliques(G):
        if len(check) != 3:
            continue
        for item in check:
            if 't' == item[0]:
                count += 1
                break

    print(count)
    return 0


if __name__ == '__main__':
    main()
