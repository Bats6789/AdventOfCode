/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/25/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

typedef char node_name[4];

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

void add_edge(graph_t *graph, const node_name start, const node_name stop);
edge_t minimum_edge_cut(graph_t graph);
size_t connected_components(graph_t source, graph_t **graphs);
void remove_edge(graph_t *graph, edge_t edge);
void free_graph(graph_t *graph);
graph_t init_graph(void);

int main(int argc, char **argv) {
    FILE *file;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void add_edge(graph_t *graph, const node_name start, const node_name stop);
edge_t minimum_edge_cut(graph_t graph);
size_t connected_components(graph_t source, graph_t **graphs);
void remove_edge(graph_t *graph, edge_t edge);

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
