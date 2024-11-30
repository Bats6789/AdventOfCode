/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 21 of AOC.
 * Vers: 1.0.0 12/21/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	size_t x;
	size_t y;
	size_t step;
} node_t;

typedef struct {
	node_t *nodes;
	size_t sz;
	size_t cap;
} queue_t;

typedef struct {
    char *cells;
    size_t height;
    size_t width;
    size_t sz;
} grid_t;

queue_t queueInit(void) {
	queue_t queue = {NULL, 0, 1000};

	queue.nodes = malloc(sizeof(*queue.nodes) * queue.cap);

	return queue;
}

void enqueue(queue_t *queue, node_t node) {
	if (queue->sz >= queue->cap) {
		queue->cap *= 2;
		queue->nodes = realloc(queue->nodes, sizeof(*queue->nodes) * queue->cap);
	}

	queue->nodes[queue->sz++] = node;
}

node_t dequeu(queue_t *queue) {
	if (!queue || queue->sz == 0) { return (node_t){0, 0, 0}; }

	node_t node = queue->nodes[0];

	queue->sz--;
	for (size_t i = 0; i < queue->sz; ++i) {
		queue->nodes[i] = queue->nodes[i + 1];
	}

	return node;
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

node_t getStart(grid_t grid) {
	node_t start = {0, 0, 0};

	for (size_t i = 0; i < grid.height; ++i) {
		for (size_t j = 0; j < grid.width; ++j) {
			if (grid.cells[i * grid.width + j] == 'S') {
				start.x = j;
				start.y = i;
				return start;
			}
		}
	}

	return start;
}

void freeQueue(queue_t *queue) {
	free(queue->nodes);
	queue->nodes = NULL;
	queue->sz = 0;
	queue->cap = 0;
}

size_t fill(grid_t grid, node_t start) {
	node_t node;
	node_t tmpNode;
	queue_t queue;
	queue_t ans;
	size_t key;
	size_t answer;
	bool *seen = NULL;

	seen = malloc(sizeof(*seen) * grid.sz);

	for (size_t i = 0; i < grid.sz; ++i) {
		seen[i] = false;
	}

	queue = queueInit();
	ans = queueInit();

	enqueue(&queue, start);

	while (queue.sz) {
		node = dequeu(&queue);

		if (node.step % 2 == 0) {
			enqueue(&ans, node);
		}

		if (node.step == 0) {
			continue;
		}

		tmpNode.x = node.x + 1;
		tmpNode.y = node.y;
		tmpNode.step = node.step - 1;
		key = tmpNode.y * grid.width + tmpNode.x;
		if (tmpNode.x < grid.width && grid.cells[key] == '.' && !seen[key]) {
			seen[key] = true;
			enqueue(&queue, tmpNode);
		}

		tmpNode.x = node.x - 1;
		tmpNode.y = node.y;
		key = tmpNode.y * grid.width + tmpNode.x;
		if (node.x > 0 && grid.cells[key] == '.' && !seen[key]) {
			seen[key] = true;
			enqueue(&queue, tmpNode);
		}

		tmpNode.x = node.x;
		tmpNode.y = node.y - 1;
		key = tmpNode.y * grid.width + tmpNode.x;
		if (node.y > 0 && grid.cells[key] == '.' && !seen[key]) {
			seen[key] = true;
			enqueue(&queue, tmpNode);
		}

		tmpNode.x = node.x;
		tmpNode.y = node.y + 1;
		key = tmpNode.y * grid.width + tmpNode.x;
		if (tmpNode.y < grid.height && grid.cells[key] == '.' && !seen[key]) {
			seen[key] = true;
			enqueue(&queue, tmpNode);
		}
	}



	answer = ans.sz;

	free(seen);
	freeQueue(&queue);
	freeQueue(&ans);

	return answer;
}

static inline size_t sizeSq(size_t x) { return x * x; }

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	node_t start;
	node_t node;
	size_t steps;
	size_t size;
	size_t gridWidth;
	size_t oddCount;
	size_t evenCount;
	size_t oddPoints;
	size_t evenPoints;
	size_t corner_t;
	size_t corner_r;
	size_t corner_b;
	size_t corner_l;
	size_t small_tr;
	size_t small_tl;
	size_t small_br;
	size_t small_bl;
	size_t large_tr;
	size_t large_tl;
	size_t large_br;
	size_t large_bl;
	size_t cornerSum;
	size_t smallSum;
	size_t largeSum;

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
	start = getStart(grid);

	start.step = 64;

	steps = 26501365;
	size = grid.height;
	gridWidth = steps / size - 1;

	oddCount = sizeSq((gridWidth / 2) * 2 + 1);
	evenCount = sizeSq(((gridWidth + 1) / 2) * 2);

	node.x = start.x;
	node.y = start.y;
	node.step = 2 * size + 1;
	oddPoints = fill(grid, node);
	node.step = 2 * size;
	evenPoints = fill(grid, node);

	node.x = start.x;
	node.y = size - 1;
	node.step = size - 1;
	corner_t = fill(grid, node);
	node.x = 0;
	node.y = start.y;
	corner_r = fill(grid, node);
	node.x = start.x;
	node.y = 0;
	corner_b = fill(grid, node);
	node.x = size - 1;
	node.y = start.y;
	corner_l = fill(grid, node);

	node.x = 0;
	node.y = size - 1;
	node.step = size / 2 - 1;
	small_tr = fill(grid, node);
	node.x = size - 1;
	node.y = size - 1;
	small_tl = fill(grid, node);
	node.x = 0;
	node.y = 0;
	small_br = fill(grid, node);
	node.x = size - 1;
	node.y = 0;
	small_bl = fill(grid, node);

	node.x = 0;
	node.y = size - 1;
	node.step = 3 * size / 2 - 1;
	large_tr = fill(grid, node);
	node.x = size - 1;
	node.y = size - 1;
	large_tl = fill(grid, node);
	node.x = 0;
	node.y = 0;
	large_br = fill(grid, node);
	node.x = size - 1;
	node.y = 0;
	large_bl = fill(grid, node);

	cornerSum = corner_b + corner_l + corner_t + corner_r;
	smallSum = small_tr + small_tl + small_br + small_bl;
	largeSum = large_tr + large_tl + large_br + large_bl;

	printf("%zu\n", oddCount * oddPoints + evenCount * evenPoints + cornerSum +
		(gridWidth + 1) * smallSum + gridWidth * largeSum);
    return EXIT_SUCCESS;
}
