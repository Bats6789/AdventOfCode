/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 17 of AOC.
 * Vers: 1.0.0 12/17/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { left = 0, right = 1, up = 2, down = 3 } dir_t;

typedef struct {
    int x;
    int y;
    int heatLoss;
    dir_t dir;
    size_t steps;
} node_t;

typedef struct {
	node_t *heap;
	size_t count;
	size_t sz;
} heap_t;

typedef struct {
    char *cells;
    size_t height;
    size_t width;
    size_t sz;
} grid_t;

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

heap_t *createHeap(void) {
	heap_t *heap = malloc(sizeof(*heap));

	if (heap == NULL) {
		perror("ERROR");
		return NULL;
	}

	heap->sz = 100;
	heap->count = 0;

	heap->heap = malloc(sizeof(*heap->heap) * heap->sz);

	return heap;
}

void insertHelper(heap_t *heap, int index) {
	int parent = (index - 1) / 2;

	if (heap->heap[parent].heatLoss > heap->heap[index].heatLoss) {
		node_t temp = heap->heap[parent];
		heap->heap[parent] = heap->heap[index];
		heap->heap[index] = temp;

		insertHelper(heap, parent);
	}
}

void insert(heap_t *heap, node_t data) {
	if (heap->count >= heap->sz) {
		heap->sz *= 2;
		heap->heap = realloc(heap->heap, sizeof(*heap->heap) * heap->sz);
	}

	heap->heap[heap->count] = data;

	insertHelper(heap, heap->count);

	heap->count++;
}

void minHeapify(heap_t *heap, int index) {
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int min = index;

	if (left >= heap->count || left < 0) {
		left = -1;
	}
	if (right >= heap->count || right < 0) {
		right = -1;
	}

	if (left != -1 && heap->heap[left].heatLoss < heap->heap[index].heatLoss) {
		min = left;
	}
	if (right != -1 && heap->heap[right].heatLoss < heap->heap[min].heatLoss) {
		min = right;
	}

	if (min != index) {
		node_t temp = heap->heap[min];
		heap->heap[min] = heap->heap[index];
		heap->heap[index] = temp;

		minHeapify(heap, min);
	}
}

node_t extractMin(heap_t *heap) {
	node_t deleteItem = {0, 0, 0};

	if (heap->count == 0) {
		fprintf(stderr, "ERROR: Heap is empty\n");
		return deleteItem;
	}

	deleteItem = heap->heap[0];

	heap->heap[0] = heap->heap[--heap->count];

	minHeapify(heap, 0);
	return deleteItem;
}

int minHeatLoss(grid_t grid) {
    int heatLoss = 0;
    bool *seen = malloc(11 * 4 * grid.sz * sizeof(*seen));
	heap_t *queue = createHeap();
    node_t node;
    node_t tmpNode;
    int key;
    int lookupKey;
    int nx;
    int ny;

    for (size_t i = 0; i < grid.sz * 11 * 4; ++i) {
        seen[i] = false;
    }

    // add node for right
    node.x = 1;
    node.y = 0;
    node.heatLoss = grid.cells[1] - '0';
    node.dir = right;
    node.steps = 1;

    insert(queue, node);

    // add node for down
    node.x = 0;
    node.y = 1;
    node.heatLoss = grid.cells[grid.width] - '0';
    node.dir = down;
    node.steps = 1;

    insert(queue, node);

    while (queue->count > 0) {
        node = extractMin(queue);

        if (node.x == grid.width - 1 && node.y == grid.height - 1) {
            return node.heatLoss;
        }

        if (node.x < 0 || node.x >= grid.width || node.y < 0 ||
            node.y >= grid.height) {
            continue;
        }

        key = node.x + node.y * grid.width + node.steps * grid.sz +
              node.dir * 11 * grid.sz;

        if (seen[key] || node.heatLoss == -1) {
            continue;
        }

        switch (node.dir) {
            case left:
                nx = node.x - 1;
                ny = node.y;
                break;
            case right:
                nx = node.x + 1;
                ny = node.y;
                break;
            case up:
                nx = node.x;
                ny = node.y - 1;
                break;
            case down:
                nx = node.x;
                ny = node.y + 1;
                break;
        }

        if (node.steps < 10 && 0 <= nx && nx < grid.width && 0 <= ny &&
            ny < grid.height) {
            seen[key] = true;
            lookupKey = ny * grid.width + nx;
            tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
            tmpNode.x = nx;
            tmpNode.y = ny;
            tmpNode.dir = node.dir;
            tmpNode.steps = node.steps + 1;
            insert(queue, tmpNode);
        }

        if (node.dir != up && node.dir != down && node.steps > 3) {
            if (node.y > 0) {
                lookupKey = (node.y - 1) * grid.width + node.x;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x;
                tmpNode.y = node.y - 1;
                tmpNode.dir = up;
                tmpNode.steps = 1;
                insert(queue, tmpNode);
            }

            if (node.y < grid.height - 1) {
                lookupKey = (node.y + 1) * grid.width + node.x;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x;
                tmpNode.y = node.y + 1;
                tmpNode.dir = down;
                tmpNode.steps = 1;
                insert(queue, tmpNode);
            }
        }

        if (node.dir != left && node.dir != right && node.steps > 3) {
            if (node.x > 0) {
                lookupKey = node.y * grid.width + node.x - 1;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x - 1;
                tmpNode.y = node.y;
                tmpNode.dir = left;
                tmpNode.steps = 1;
                insert(queue, tmpNode);
            }

            if (node.x < grid.width - 1) {
                lookupKey = node.y * grid.width + node.x + 1;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x + 1;
                tmpNode.y = node.y;
                tmpNode.dir = right;
                tmpNode.steps = 1;
                insert(queue, tmpNode);
            }
        }
    }

    return heatLoss;
}

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;

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

    printf("%d\n", minHeatLoss(grid));

    return EXIT_SUCCESS;
}
