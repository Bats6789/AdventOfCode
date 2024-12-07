/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/25/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_NAME_SZ 4

typedef char node_name[NODE_NAME_SZ];

typedef struct edge {
    node_name a;
    node_name b;
} edge_t;

typedef struct graph {
    node_name *nodes;
    edge_t *edges;
    size_t node_max;
    size_t edge_max;
    size_t node_sz;
    size_t edge_sz;
} graph_t;

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

void add_node(graph_t *graph, const node_name node);
void add_edge(graph_t *graph, const node_name start, const node_name stop);
void dft(graph_t graph, size_t index, size_t parent, int *desc, int *low, bool *visited, bool *ap);
size_t minimum_edge_cut(graph_t graph, edge_t **edges);
void edge_cpy(edge_t *dest, edge_t *src);
size_t find_node(graph_t graph, node_name node);
size_t find_edge(graph_t graph, edge_t edge);
graph_t BFS_connection(graph_t source, size_t i, bool *visited);
size_t connected_components(graph_t source, graph_t **graphs);
void remove_edge(graph_t *graph, edge_t edge);
void free_graph(graph_t *graph);
graph_t init_graph(void);
bool edge_equal(edge_t left, edge_t right);
void read_line(FILE *file, string_t *str);
string_t init_str(void);
void free_str(string_t *str);

int main(int argc, char **argv) {
    FILE *file;
	string_t string = init_str();
	node_name left;
	node_name right;
	graph_t graph = init_graph();
	char *tok;
	char *tmp;
	edge_t *edges;
	size_t graphs_sz = 0;
	size_t edge_sz = 0;
	graph_t *graphs = NULL;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	while (!feof(file)) {
		read_line(file, &string);
		if (string.len <= 3) {
			continue;
		}

		string.str[3] = '\0';
		strncpy(left, string.str, NODE_NAME_SZ);
		left[NODE_NAME_SZ - 1] = '\0';

		tmp = string.str + 5; // move past first space

		tok = strtok(tmp, " ");

		while (tok != NULL) {
			strncpy(right, tok, NODE_NAME_SZ);
			add_edge(&graph, left, right);
			tok = strtok(NULL, " ");
		}
	}
	free_str(&string);

	edge_sz = minimum_edge_cut(graph, &edges);

	if (edge_sz != 3) {
		fprintf(stderr, "Failed to only find 3 edges\nFound: %zu\n", edge_sz);
		return -1;
	}

	for (size_t i = 0; i < edge_sz; ++i) {
		remove_edge(&graph, edges[i]);
	}
	graphs_sz = connected_components(graph, &graphs);

	printf("%zu\n", graphs[0].node_sz * graphs[1].node_sz);

	free_graph(&graph);
	for (size_t i = 0; i < graphs_sz; ++i) {
		free_graph(graphs + i);
	}
	free(graphs);

    return EXIT_SUCCESS;
}

void add_node(graph_t *graph, const node_name node) {
    bool found_node = false;
    if (graph == NULL) {
        return;
    }

    if (graph->edges == NULL) {
        graph->edge_max = graph->edge_max == 0 ? 100 : graph->edge_max;
        graph->edges = malloc(sizeof *graph->edges * graph->edge_max);
    }

    if (graph->nodes == NULL) {
        graph->node_max = graph->node_max == 0 ? 100 : graph->node_max;
        graph->nodes = malloc(sizeof *graph->nodes * graph->node_max);
    }

    for (size_t i = 0; i < graph->node_sz && !found_node; ++i) {
        if (strncmp(graph->nodes[i], node, NODE_NAME_SZ) == 0) {
            found_node = true;
        }
    }

    if (!found_node) {
        strncpy(graph->nodes[graph->node_sz++], node, NODE_NAME_SZ);
    }

    if (graph->node_sz >= graph->node_max) {
        graph->node_max *= 2;
        graph->nodes = realloc(graph->nodes, sizeof *graph->nodes * graph->node_max);
    }
}

void add_edge(graph_t *graph, const node_name start, const node_name stop) {
    edge_t edge;
    bool found_start = false;
    bool found_stop = false;
    bool found_edge = false;

    if (graph == NULL) {
        return;
    }

    if (graph->edges == NULL) {
        graph->edge_max = graph->edge_max == 0 ? 100 : graph->edge_max;
        graph->edges = malloc(sizeof *graph->edges * graph->edge_max);
    }

    if (graph->nodes == NULL) {
        graph->node_max = graph->node_max == 0 ? 100 : graph->node_max;
        graph->nodes = malloc(sizeof *graph->nodes * graph->node_max);
    }

    strncpy(edge.a, start, NODE_NAME_SZ);
    strncpy(edge.b, stop, NODE_NAME_SZ);

    for (size_t i = 0; i < graph->node_sz; ++i) {
        if (strncmp(graph->nodes[i], start, NODE_NAME_SZ) == 0) {
            found_start = true;
        }

        if (strncmp(graph->nodes[i], stop, NODE_NAME_SZ) == 0) {
            found_stop = true;
        }
    }

    if (!found_start) {
        add_node(graph, start);
    }

    if (!found_stop) {
        add_node(graph, stop);
    }

    for (size_t i = 0; i < graph->edge_sz; ++i) {
        if (edge_equal(graph->edges[i], edge)) {
            found_edge = true;
        }
    }

    if (!found_edge) {
        edge_cpy(graph->edges + graph->edge_sz++, &edge);

        if (graph->edge_sz >= graph->edge_max) {
            graph->edge_max *= 2;
            graph->edges = realloc(graph->edges, sizeof *graph->edges * graph->edge_max);
        }
    }
}

void dft(graph_t graph, size_t index, size_t parent, int *disc, int *low, bool *visited, bool *ap) {
	node_name *adj;
	size_t *adj_index;
	size_t adj_max = 10;
	size_t adj_sz = 0;
	size_t found_index;

	static int time = 0;

	if (visited[index]) {
		return;
	}

	visited[index] = true;
	disc[index] = low[index] = time++;

	adj = malloc(sizeof *adj * adj_max);
	adj_index = malloc(sizeof *adj_index * adj_max);

	// collect adjacent nodes
    for (size_t i = 0; i < graph.edge_sz; ++i) {
        if (strncmp(graph.nodes[index], graph.edges[i].a, NODE_NAME_SZ) == 0) {
            found_index = find_node(graph, graph.edges[i].b);
			adj_index[adj_sz] = found_index;
			strncpy(adj[adj_sz++], graph.edges[i].b, NODE_NAME_SZ);
        } else if (strncmp(graph.nodes[index], graph.edges[i].b, NODE_NAME_SZ) == 0) {
            found_index = find_node(graph, graph.edges[i].a);
			adj_index[adj_sz] = found_index;
			strncpy(adj[adj_sz++], graph.edges[i].a, NODE_NAME_SZ);
        }

		if (adj_sz >= adj_max) {
			adj_max *= 2;
			adj = realloc(adj, sizeof *adj * adj_max);
			adj_index = realloc(adj_index, sizeof *adj_index * adj_max);
		}
    }

	for (size_t i = 0; i < adj_sz; ++i) {
		if (!visited[adj_index[i]]) {
			dft(graph, adj_index[i], index, disc, low, visited, ap);
		}
	}

	for (size_t i = 0; i < adj_sz; ++i) {
		if (parent != adj_index[i]) {
			low[index] = low[index] < low[adj_index[i]] ? low[index] : low[adj_index[i]];
		}
	}

	if (low[index] < low[parent]) {
		low[parent] = low[index];
	}

	if (disc[parent] < low[index]) {
		edge_t tmp;
		strncpy(tmp.a, graph.nodes[parent], NODE_NAME_SZ);
		strncpy(tmp.b, graph.nodes[index], NODE_NAME_SZ);
		size_t edge_index = find_edge(graph, tmp);
		ap[edge_index] = true;
	}
}

size_t minimum_edge_cut(graph_t graph, edge_t **edges) {
	edge_t edge;
	size_t ap_sz = 0;
	int *disc;
	int *low;
	bool *visited;
	bool *ap;
	size_t edge_sz = 0;
	size_t edge_max = 10;

	disc = malloc(sizeof *disc * graph.node_sz);
	low = malloc(sizeof *low * graph.node_sz);
	visited = malloc(sizeof *visited * graph.node_sz);
	ap = malloc(sizeof *ap * graph.edge_sz);

	for (size_t i = 0; i < graph.node_sz; ++i) {
		disc[i] = -1;
		low[i] = -1;
		visited[i] = false;
	}

	for (size_t i = 0; i < graph.edge_sz; ++i) {
		ap[i] = false;
	}

	dft(graph, 0, 0, disc, low, visited, ap);

	for (size_t i = 0; i < graph.node_sz; ++i) {
		fprintf(stderr, "low[%zu]: %s = %d\n", i, graph.nodes[i], low[i]);
	}

	*edges = malloc(sizeof **edges * edge_max);

	for (size_t i = 0; i < graph.edge_sz; ++i) {
		if (ap[i]) {
			edge_cpy(*edges + edge_sz++, graph.edges + i);

			if (edge_sz >= edge_max) {
				edge_max *= 2;
				*edges = realloc(*edges, sizeof **edges * edge_max);
			}
		}
	}

	*edges = realloc(*edges, sizeof **edges * edge_sz);

	return edge_sz;
}

void edge_cpy(edge_t *dest, edge_t *src) {
    strncpy(dest->a, src->a, NODE_NAME_SZ);
    strncpy(dest->b, src->b, NODE_NAME_SZ);
}

size_t find_edge(graph_t graph, edge_t edge) {
    for (size_t i = 0; i < graph.edge_sz; ++i) {
        if (edge_equal(graph.edges[i], edge)) {
            return i;
        }
    }

    return 0;
}

size_t find_node(graph_t graph, node_name node) {
    for (size_t i = 0; i < graph.node_sz; ++i) {
        if (strncmp(graph.nodes[i], node, NODE_NAME_SZ) == 0) {
            return i;
        }
    }

    return 0;
}

graph_t BFS_connection(graph_t source, size_t index, bool *visited) {
    graph_t graph = init_graph();
    size_t q_sz = 0;
    size_t q_max = 10;
    size_t found_index = 0;
    node_name *q = NULL;
    node_name tmp;

    visited[index] = true;

    add_node(&graph, source.nodes[index]);

    q = malloc(sizeof *q * q_max);

    for (size_t i = 0; i < source.edge_sz; ++i) {
        if (strncmp(source.nodes[index], source.edges[i].a, NODE_NAME_SZ) == 0) {
            found_index = find_node(source, source.edges[i].b);
            if (!visited[found_index]) {
                strncpy(q[q_sz++], source.edges[i].b, NODE_NAME_SZ);
                add_edge(&graph, source.edges[i].a, source.edges[i].b);

                if (q_sz >= q_max) {
                    q_max *= 2;
                    q = realloc(q, sizeof *q * q_max);
                }
            }
        } else if (strncmp(source.nodes[index], source.edges[i].b, NODE_NAME_SZ) == 0) {
            found_index = find_node(source, source.edges[i].a);
            if (!visited[found_index]) {
                strncpy(q[q_sz++], source.edges[i].a, NODE_NAME_SZ);
                add_edge(&graph, source.edges[i].a, source.edges[i].b);

                if (q_sz >= q_max) {
                    q_max *= 2;
                    q = realloc(q, sizeof *q * q_max);
                }
            }
        }
    }

    while (q_sz > 0) {
        strncpy(tmp, q[0], NODE_NAME_SZ);
        index = find_node(source, tmp);

        if (!visited[index]) {
            visited[index] = true;
            for (size_t i = 0; i < source.edge_sz; ++i) {
                if (strncmp(source.nodes[index], source.edges[i].a, NODE_NAME_SZ) == 0) {
                    found_index = find_node(source, source.edges[i].b);
                    if (!visited[found_index]) {
                        strncpy(q[q_sz++], source.edges[i].b, NODE_NAME_SZ);
                        add_edge(&graph, source.edges[i].a, source.edges[i].b);
                    }
                } else if (strncmp(source.nodes[index], source.edges[i].b, NODE_NAME_SZ) == 0) {
                    found_index = find_node(source, source.edges[i].a);
                    if (!visited[found_index]) {
                        strncpy(q[q_sz++], source.edges[i].a, NODE_NAME_SZ);
                        add_edge(&graph, source.edges[i].a, source.edges[i].b);
                    }
                }

				if (q_sz >= q_max) {
					q_max *= 2;
					q = realloc(q, sizeof *q * q_max);
				}
			}
        }

        q_sz--;
        for (size_t i = 0; i < q_sz; ++i) {
            strncpy(q[i], q[i + 1], NODE_NAME_SZ);
        }
    }

    free(q);

    return graph;
}

size_t connected_components(graph_t source, graph_t **graphs) {
    size_t graphs_count = 0;
    bool *visited;
    size_t graphs_max = 10;

    if (graphs == NULL) {
        return 0;
    }

    visited = malloc(sizeof *visited * source.node_sz);
    for (size_t i = 0; i < source.node_sz; ++i) {
        visited[i] = false;
    }

    *graphs = malloc(sizeof **graphs * graphs_max);

    for (size_t i = 0; i < source.node_sz; ++i) {
        if (!visited[i]) {
            (*graphs)[graphs_count++] = BFS_connection(source, i, visited);
			if (graphs_count >= graphs_max) {
				graphs_max *= 2;
				*graphs = realloc(*graphs, sizeof **graphs * graphs_max);
			}
        }
    }

    *graphs = realloc(*graphs, sizeof **graphs * graphs_count);

    return graphs_count;
}

void remove_edge(graph_t *graph, edge_t edge) {
    if (graph == NULL || graph->edges == NULL || graph->nodes == NULL || graph->edge_sz == 0) {
        return;
    }

    for (size_t i = 0; i < graph->edge_sz; ++i) {
        if (edge_equal(graph->edges[i], edge)) {
            for (size_t j = i; j < graph->edge_sz - 1; ++j) {
                graph->edges[j] = graph->edges[j + 1];
            }
            graph->edge_sz--;
            i--;  // need to recheck this item
        }
    }
}

void free_graph(graph_t *graph) {
    if (graph == NULL) {
        return;
    }

    if (graph->nodes != NULL) {
        free(graph->nodes);
        graph->nodes = NULL;
        graph->node_max = 0;
        graph->node_sz = 0;
    }

    if (graph->edges != NULL) {
        free(graph->edges);
        graph->edges = NULL;
        graph->edge_max = 0;
        graph->edge_sz = 0;
    }
}

graph_t init_graph(void) {
    graph_t graph = {NULL, NULL, 100, 100, 0, 0};
    graph.nodes = malloc(sizeof *graph.nodes * graph.node_max);
    graph.edges = malloc(sizeof *graph.edges * graph.edge_max);

    return graph;
}

bool edge_equal(edge_t left, edge_t right) {
    if (strncmp(left.a, right.a, NODE_NAME_SZ) == 0) {
        return strncmp(left.b, right.b, NODE_NAME_SZ) == 0;
    } else if (strncmp(left.b, right.a, NODE_NAME_SZ) == 0) {
        return strncmp(left.a, right.b, NODE_NAME_SZ) == 0;
    }

    return false;
}

void read_line(FILE *file, string_t *str) {
	char c;
	str->len = 0;

	if (str->cap == 0) {
		str->cap = 100;
		str->str = calloc(str->cap, sizeof *str->str);
	}

	while ((c = fgetc(file)) != EOF && c != '\n') {
		str->str[str->len++] = c;

		if (str->len >= str->cap) {
			str->cap *= 2;
			str->str = realloc(str->str, sizeof *str->str * str->cap);
		}
	}

	str->str[str->len++] = '\0';
}

string_t init_str(void) {
	string_t str = {NULL, 0, 100};
	str.str = calloc(str.cap, sizeof *str.str);

	return str;
}

void free_str(string_t *str) {
	if (str == NULL) {
		return;
	}

	if (str->str != NULL) {
		free(str->str);
		str->str = NULL;
		str->cap = 0;
		str->len = 0;
	}
}
