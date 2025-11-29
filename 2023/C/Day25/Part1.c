/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 25 of AOC.
 * Vers: 1.0.0 12/25/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct list {
	node_name name;
	struct list *next;
} list_t;

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
	fclose(file);

	srand(time(NULL));
	edge_sz = minimum_edge_cut(graph, &edges);
	while (edge_sz != 3) {
		free(edges);
		edges = NULL;
		edge_sz = minimum_edge_cut(graph, &edges);
	}

	if (edge_sz != 3) {
		fprintf(stderr, "Failed to only find 3 edges\nFound: %zu\n", edge_sz);
		return -1;
	}

	for (size_t i = 0; i < edge_sz; ++i) {
		remove_edge(&graph, edges[i]);
	}
	graphs_sz = connected_components(graph, &graphs);

	if (graphs_sz != 2) {
		fprintf(stderr, "Failed to split graph into 2. Got %zu graphs instead\n", graphs_sz);
		exit(EXIT_FAILURE);
	}

	printf("%zu\n", graphs[0].node_sz * graphs[1].node_sz);

	free_graph(&graph);
	for (size_t i = 0; i < graphs_sz; ++i) {
		free_graph(graphs + i);
	}
	free(graphs);
	free(edges);

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

bool in_list(list_t *list, const node_name name) {
	if (list == NULL) {
		return false;
	}

	return strncmp(list->name, name, NODE_NAME_SZ) == 0 || in_list(list->next, name);
}

void append_list(list_t *left, list_t *right) {
	while (left->next != NULL) {
		left = left->next;
	}

	left->next = right;
}

size_t minimum_edge_cut(graph_t graph, edge_t **edges) {
	edge_t edge;
	size_t edge_sz = 0;
	size_t edge_max = 10;
	graph_t dup_graph;
	size_t rand_ind = 0;
	list_t **node_list = NULL;
	size_t list_max = 10;
	size_t list_sz = 0;
	ssize_t left_list = -1;
	ssize_t right_list = -1;
	bool compress = false;

	// duplicate graph
	dup_graph.edge_sz = graph.edge_sz;
	dup_graph.edge_max = graph.edge_max;
	dup_graph.node_sz = graph.node_sz;
	dup_graph.node_max = graph.node_max;

	dup_graph.nodes = malloc(sizeof *dup_graph.nodes * dup_graph.node_max);
	dup_graph.edges = malloc(sizeof *dup_graph.edges * dup_graph.edge_max);

	node_list = malloc(sizeof *node_list * list_max);
	memset(node_list, 0, sizeof *node_list * list_max);

	memcpy(dup_graph.nodes, graph.nodes, sizeof *graph.nodes * graph.node_sz);
	memcpy(dup_graph.edges, graph.edges, sizeof *graph.edges * graph.edge_sz);

	// compress nodes to two
	while (list_sz + dup_graph.node_sz > 2) {
		rand_ind = rand() % dup_graph.edge_sz;

		edge = dup_graph.edges[rand_ind];

		left_list = -1;
		right_list = -1;

		bool swap = false;

		for (ssize_t i = 0; i < list_sz && (left_list == -1 || right_list == -1); ++i) {
			if (left_list == -1 && in_list(node_list[i], edge.a)) {
				left_list = i;
			}
			if (right_list == -1 && in_list(node_list[i], edge.b)) {
				right_list = i;
			}
		}


		if (left_list != -1 && right_list != -1 && left_list > right_list || left_list == -1) {
			ssize_t tmp = left_list;
			left_list = right_list;
			right_list = tmp;
			swap = true;
		}


		if (left_list != right_list && left_list != -1 && right_list != -1) {
			append_list(node_list[left_list], node_list[right_list]);

			for (size_t i = right_list; i < list_sz - 1; ++i) {
				node_list[i] = node_list[i + 1];
			}

			list_sz--;
		} else if (left_list != -1 && left_list != right_list) {
			list_t *tmp = node_list[left_list];

			while (tmp->next != NULL) {
				tmp = tmp->next;
			}

			tmp->next = malloc(sizeof *tmp);
			tmp = tmp->next;
			tmp->next = NULL;
			strncpy(tmp->name, swap ? edge.a : edge.b, NODE_NAME_SZ);

			dup_graph.node_sz--;
		} else if(left_list == -1 && right_list == -1) {
			node_list[list_sz] = malloc(sizeof **node_list);

			strncpy(node_list[list_sz]->name, edge.a, NODE_NAME_SZ);
			node_list[list_sz]->next = malloc(sizeof **node_list);

			strncpy(node_list[list_sz]->next->name, edge.b, NODE_NAME_SZ);
			node_list[list_sz]->next->next = NULL;

			list_sz++;
			dup_graph.node_sz -= 2;
		}

		if (list_sz >= list_max) {
			list_max += 10;
			node_list = realloc(node_list, sizeof *node_list * list_max);
		}

		remove_edge(&dup_graph, edge);
	}

	// remove loops
	do {
		compress = false;

		for (size_t i = 0; i < dup_graph.edge_sz && !compress; ++i) {
			left_list = -1;
			right_list = -1;
			edge = dup_graph.edges[i];

			for (size_t j = 0; j < list_sz && (left_list == -1 || right_list == -1); ++j) {
				if (left_list == -1 && in_list(node_list[j], edge.a)) {
					left_list = j;
				}
				if (right_list == -1 && in_list(node_list[j], edge.b)) {
					right_list = j;
				}
			}

			if (left_list == right_list && left_list != -1) {
				remove_edge(&dup_graph, edge);
				compress = true;
			}
		}
	} while(compress);

	edge_sz = dup_graph.edge_sz;
	*edges = malloc(sizeof **edges * edge_sz);
	for (size_t i = 0; i < edge_sz; ++i) {
		(*edges)[i] = dup_graph.edges[i];
	}

	for (size_t i = 0; i < list_sz; ++i) {
		list_t *tmp = node_list[i];
		list_t *next;

		while (tmp) {
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
	}

	free(node_list);
	free_graph(&dup_graph);

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

	free(visited);

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
