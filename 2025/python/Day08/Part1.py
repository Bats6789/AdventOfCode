import sys
import networkx as nx
from itertools import combinations


class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


    def __str__(self):
        return f"({self.x},{self.y},{self.z})"


    def __repr__(self):
        return self.__str__()


    def from_str(str):
        x, y, z = tuple(map(int, str.split(',')))

        return Point(x, y, z)


    def distance(self, point: Point):
        return ((self.x - point.x)**2 + (self.y - point.y)**2 + (self.z - point.z)**2)**0.5


def main():
    file = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    data = open(file).read().strip()

    points = list(map(Point.from_str, data.split('\n')))

    graph = nx.Graph()
    graph.add_nodes_from(points)

    for p1, p2 in combinations(points, 2):
        graph.add_edge(p1, p2, weight=p1.distance(p2))

    edge_weights = sorted(graph.edges(data=True), key=lambda edge: edge[2].get('weight', 1))
    con_graph = nx.Graph()
    con_graph.add_nodes_from(points)
    for i in range(1000):
        if len(edge_weights) == 0:
            break
        edge = edge_weights.pop(0)
        con_graph.add_edge(edge[0], edge[1], weight=edge[2].get('weight', 1))

    connected_components = list(nx.connected_components(con_graph))
    graph_sizes = sorted(list(map(len, connected_components)), reverse=True)

    print(graph_sizes[0] * graph_sizes[1] * graph_sizes[2])

    return 0


if __name__ == '__main__':
    main()
