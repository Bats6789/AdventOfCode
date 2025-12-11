import sys
import networkx as nx


memoize = {}


def path_lists_count(dg, src, dst, filter):
    str_map = src + '-' + '-'.join(filter)
    if str_map in memoize:
        return memoize[str_map]

    if src == dst:
        if filter == []:
            memoize[str_map] = 1
            return 1
        else:
            memoize[str_map] = 0
            return 0

    count = 0

    edges = dg.edges(src)

    for edge in edges:
        if edge[1] in filter:
            tmp_filter = [el for el in filter if el != edge[1]]
            count += path_lists_count(dg, edge[1], dst, tmp_filter)
        else:
            count += path_lists_count(dg, edge[1], dst, filter)

    memoize[str_map] = count

    return count


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    dg = nx.DiGraph()

    for line in data.split('\n'):
        src, targets = line.split(': ')

        targets = targets.split()

        for target in targets:
            dg.add_edge(src, target)

    print(path_lists_count(dg, "svr", "out", ["dac", "fft"]))

    return 0


if __name__ == '__main__':
    main()
