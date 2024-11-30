/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 23 of AOC.
 * Vers: 1.0.0 12/23/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    point_t pt;
    size_t dist;
} node_t;

typedef struct {
    node_t *nodes;
    size_t sz;
    size_t cap;
} stack_t;

typedef struct {
    point_t node;
    node_t *edges;
    size_t edgeSz;
    size_t edgeCap;
} graph_t;

typedef struct {
    char *cells;
    size_t height;
    size_t width;
    size_t sz;
} grid_t;

typedef struct {
    point_t *el;
    size_t sz;
    size_t cap;
} array_t;

bool elInArray(point_t el, array_t array) {
    bool ans = false;

    for (size_t i = 0; i < array.sz && !ans; ++i) {
        if (array.el[i].x == el.x && array.el[i].y == el.y) {
            ans = true;
        }
    }

    return ans;
}

array_t initArray(void) {
    array_t array = {NULL, 0, 10};

    array.el = malloc(sizeof(*array.el) * array.cap);

    return array;
}

void addEl(array_t *array, point_t el) {
    if (!array) {
        return;
    }

    if (array->cap == 0) {
        array->cap = 10;
        array->el = malloc(sizeof(*array->el) * array->cap);
    }

    if (array->sz >= array->cap) {
        array->cap *= 2;
        array->el = realloc(array->el, sizeof(*array->el) * array->cap);
    }

    array->el[array->sz++] = el;
}

void clearArray(array_t *array) {
    free(array->el);
    array->el = NULL;
    array->sz = 0;
    array->cap = 0;
}

point_t getElAtIndex(array_t array, size_t i) {
    if (i >= array.sz) {
        return (point_t){-1, -1};
    }

    return array.el[i];
}

graph_t initGraph(void) {
    graph_t graph = {{-1, -1}, NULL, 0, 10};

    graph.edges = malloc(sizeof(*graph.edges) * graph.edgeCap);

    return graph;
}

void addEdge(graph_t *graph, node_t edge) {
    if (graph->edgeSz >= graph->edgeCap) {
        graph->edgeCap *= 2;

        graph->edges =
            realloc(graph->edges, sizeof(*graph->edges) * graph->edgeCap);
    }

    graph->edges[graph->edgeSz++] = edge;
}

stack_t initStack(void) {
    stack_t stack = {NULL, 0, 10};

    stack.nodes = malloc(sizeof(*stack.nodes) * stack.cap);

    return stack;
}

void push(stack_t *stack, node_t node) {
    if (stack->sz >= stack->cap) {
        stack->cap *= 2;

        stack->nodes =
            realloc(stack->nodes, sizeof(*stack->nodes) * stack->cap);
    }

    stack->nodes[stack->sz++] = node;
}

node_t pop(stack_t *stack) {
    if (stack->sz == 0) {
        return (node_t){{-1, -1}, 0};
    }
    return stack->nodes[--stack->sz];
}

char *readLine(FILE *file) {
    char *line = NULL;
    size_t sz = 1000;
    size_t count = 0;
    char c;

    if (feof(file)) {
        return NULL;
    }

    line = malloc(sizeof(*line) * sz);

    while ((c = getc(file)) != '\n' && c != EOF) {
        line[count++] = c;

        if (count >= sz) {
            sz *= 2;
            line = realloc(line, sizeof(*line) * sz);
        }
    }

    line[count] = '\0';

    if (count == 0) {
        free(line);
        return NULL;
    }

    return line;
}

grid_t fileToGrid(FILE *file) {
    grid_t grid = {0, 0, 0};
    char *line = NULL;
    size_t lineCount = 0;

    if (feof(file)) {
        return grid;
    }

    line = readLine(file);
    if (line == NULL) {
        return grid;
    }

    grid.width = strlen(line);
    grid.height = 10;
    grid.sz = grid.width * grid.height;
    grid.cells = malloc(sizeof(*grid.cells) * grid.width * grid.height);

    do {
        strncpy(grid.cells + lineCount++ * grid.width, line, grid.width);
        if (lineCount >= grid.height) {
            grid.height *= 2;
            grid.sz = grid.height * grid.width;
            grid.cells = realloc(grid.cells, sizeof(*grid.cells) * grid.sz);
        }
    } while ((line = readLine(file)) != NULL);

    grid.height = lineCount;
    grid.sz = grid.height * grid.width;
    grid.cells = realloc(grid.cells, sizeof(*grid.cells) * grid.sz);

    return grid;
}

bool pointInGraphs(node_t pt, graph_t *graphs, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        if (pt.pt.x == graphs[i].node.x && pt.pt.y == graphs[i].node.y) {
            return true;
        }
    }

    return false;
}

graph_t getGraph(graph_t *graphs, size_t sz, point_t pt) {
	graph_t graph = {{-1, -1}, NULL, 0, 0};

	for (size_t i = 0; i < sz; ++i) {
		if (graphs[i].node.x == pt.x &&
		    graphs[i].node.y == pt.y) {
			graph = graphs[i];
		}
	}

	return graph;
}

node_t getEdge(graph_t graph, point_t edgePt) {
	node_t node = {{-1, -1}, 0};

	for (size_t i = 0; i < graph.edgeSz; ++i) {
		if (edgePt.x == graph.edges[i].pt.x &&
			edgePt.y == graph.edges[i].pt.y) {
			node = graph.edges[i];
		}
	}

	return node;
}

void removeEl(array_t *array, point_t el) {
	for (size_t i = 0; i < array->sz; ++i) {
		if (array->el[i].x == el.x &&
		    array->el[i].y == el.y) {
			array->sz--;
			for (size_t j = i; j < array->sz; ++j) {
				array->el[j] = array->el[j + 1];
			}
			break;
		}
	}
}

size_t dfs(point_t pt, graph_t *graphs, size_t sz, point_t stop) {
	size_t m = 0;
	static array_t seen = {NULL, 0, 0};
	graph_t graph;

	if (seen.cap == 0) {
		seen.cap = 10;

		seen.el = malloc(sizeof(*seen.el) * seen.cap);
	}

	if (pt.x == stop.x && pt.y == stop.y) {
		return 0;
	}

	addEl(&seen, pt);
	graph = getGraph(graphs, sz, pt);
	for (size_t i = 0; i < graph.edgeSz; ++i) {
		point_t tmpPoint = graph.edges[i].pt;
		if (!elInArray(tmpPoint, seen)) {
			size_t tmp = dfs(tmpPoint, graphs, sz, stop) + graph.edges[i].dist;

			m = tmp > m ? tmp : m;
		}
	}
	removeEl(&seen, pt);

	if (seen.sz == 0) {
		clearArray(&seen);
	}

	return m;
}

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
    size_t neighbors;
    graph_t *graphs;
    size_t graphSz = 0;
    size_t graphCap = 100;
    stack_t stack = initStack();
    node_t node;
    array_t seen = initArray();
	point_t start;
	point_t stop;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    grid = fileToGrid(file);
    graphs = malloc(sizeof(*graphs) * graphCap);

    // start
    graphs[graphSz] = initGraph();
	start.x = 1;
	start.y = 0;
    graphs[graphSz++].node = start;
    // stop
    graphs[graphSz] = initGraph();
	stop.x = grid.width - 2;
	stop.y = grid.height - 1;
    graphs[graphSz++].node = stop;

    for (size_t i = 0; i < grid.height; ++i) {
        for (size_t j = 0; j < grid.width; ++j) {
            if (grid.cells[i * grid.width + j] == '#') {
                continue;
            }

            neighbors = 0;

            if (j > 0 && grid.cells[i * grid.width + (j - 1)] != '#') {
                neighbors++;
            }

            if (j < grid.width - 1 &&
                grid.cells[i * grid.width + (j + 1)] != '#') {
                neighbors++;
            }

            if (i > 0 && grid.cells[(i - 1) * grid.width + j] != '#') {
                neighbors++;
            }

            if (i < grid.height - 1 &&
                grid.cells[(i + 1) * grid.width + j] != '#') {
                neighbors++;
            }

            if (neighbors >= 3) {
                graphs[graphSz] = initGraph();
                graphs[graphSz].node.x = j;
                graphs[graphSz++].node.y = i;

                if (graphSz >= graphCap) {
                    graphCap *= 2;
                    graphs = realloc(graphs, sizeof(*graphs) * graphCap);
                }
            }
        }
    }

    for (size_t i = 0; i < graphSz; ++i) {
        node.pt = graphs[i].node;
        node.dist = 0;
        push(&stack, node);

        while (stack.sz) {
            node = pop(&stack);
            addEl(&seen, node.pt);

            if (node.dist != 0 && pointInGraphs(node, graphs, graphSz)) {
                addEdge(graphs + i, node);
                continue;
            }

            node_t tmp = node;
			size_t key;

            tmp.dist++;
            tmp.pt.x = node.pt.x - 1;
            tmp.pt.y = node.pt.y;
			key = tmp.pt.y * grid.width + tmp.pt.x;
            if (tmp.pt.x >= 0 && (grid.cells[key] == '.' ||
			    grid.cells[key] == '<') && !elInArray(tmp.pt, seen)) {
                push(&stack, tmp);
                addEl(&seen, tmp.pt);
            }

            tmp.pt.x = node.pt.x + 1;
            tmp.pt.y = node.pt.y;
			key = tmp.pt.y * grid.width + tmp.pt.x;
            if (tmp.pt.x < grid.width && (grid.cells[key] == '.' ||
			    grid.cells[key] == '>') && !elInArray(tmp.pt, seen)) {
                push(&stack, tmp);
                addEl(&seen, tmp.pt);
            }

            tmp.pt.x = node.pt.x;
            tmp.pt.y = node.pt.y - 1;
			key = tmp.pt.y * grid.width + tmp.pt.x; 
            if (tmp.pt.y >= 0 && (grid.cells[key] == '.' ||
			    grid.cells[key] == '^') && !elInArray(tmp.pt, seen)) {
                push(&stack, tmp);
                addEl(&seen, tmp.pt);
            }

            tmp.pt.x = node.pt.x;
            tmp.pt.y = node.pt.y + 1;
			key = tmp.pt.y * grid.width + tmp.pt.x;
            if (tmp.pt.y < grid.height && (grid.cells[key] == '.' ||
			    grid.cells[key] == 'v') && !elInArray(tmp.pt, seen)) {
                push(&stack, tmp);
                addEl(&seen, tmp.pt);
            }
        }

        clearArray(&seen);
    }

	printf("%zu\n", dfs(start, graphs, graphSz, stop));

    return EXIT_SUCCESS;
}
