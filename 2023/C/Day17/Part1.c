/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 17 of AOC.
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

typedef struct heap_t{
	node_t node;
	size_t count;
	struct heap_t *left;
	struct heap_t *right;
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

heap_t *createHeapNode(node_t node) {
	heap_t *heap = malloc(sizeof(*heap));

	heap->node = node;
	heap->count = 1;
	heap->left = NULL;
	heap->right = NULL;

	return heap;
}

void heapPush(heap_t *heap, node_t el) {
	node_t tmp;

	if (heap->count == 0) {
		heap->node = el;
		heap->count = 1;
	} else {
		if (el.heatLoss < heap->node.heatLoss) {
			tmp = heap->node;
			heap->node = el;
			el = tmp;
		}

		if (heap->left == NULL) {
			heap->left = createHeapNode(el);
		} else if(heap->right == NULL) {
			heap->right = createHeapNode(el);
		} else if(heap->left->node.heatLoss > el.heatLoss) {
			heapPush(heap->left, el);
		} else {
			heapPush(heap->right, el);
		}
		heap->count++;
	}
}

/*
void heapPush(node_t queue[SIZE], size_t count, node_t el) {
    int index = count;
    node_t tmpNode;

	if (count >= SIZE) {
		printf("uh oh\n");
		exit(-1);
	}
    queue[count] = el;

    while (index > 0 &&
           (queue[(index - 1) / 2].heatLoss > queue[index].heatLoss ||
            queue[(index - 1) / 2].heatLoss == -1)) {
        tmpNode = queue[index];
        queue[index] = queue[(index - 1) / 2];
        queue[(index - 1) / 2] = tmpNode;
        index = (index - 1) / 2;
    }
}
*/

void cleanHeap(heap_t *heap) {
	if (heap->left == NULL) {
		heap->node = heap->right->node;

		if (heap->right->count == 1) {
			free(heap->right);
			heap->right = NULL;
		} else {
			heap->right->count--;
			cleanHeap(heap->right);
		}
	} else if (heap->right == NULL) {
		heap->node = heap->left->node;

		if (heap->left->count == 1) {
			free(heap->left);
			heap->left = NULL;
		} else {
			heap->left->count--;
			cleanHeap(heap->left);
		}
	} else if (heap->left->node.heatLoss < heap->right->node.heatLoss) {
		heap->node = heap->left->node;

		if (heap->left->count == 1) {
			free(heap->left);
			heap->left = NULL;
		} else {
			heap->left->count--;
			cleanHeap(heap->left);
		}
	} else {
		heap->node = heap->right->node;

		if (heap->right->count == 1) {
			free(heap->right);
			heap->right = NULL;
		} else {
			heap->right->count--;
			cleanHeap(heap->right);
		}
	}
}

node_t heapPop(heap_t *heap) {
	node_t node = heap->node;

	heap->count--;

	if (heap->count == 0) {
		return node;
	}

	cleanHeap(heap);

	return node;
}

/*
node_t heapPop(node_t queue[SIZE], size_t count) {
    node_t node = queue[0];
    int index = 0;
    int left;
    int right;

    while (index < count) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        if ((left >= SIZE && right >= SIZE) ||
            (queue[left].heatLoss == -1 && queue[right].heatLoss == -1)) {
            break;
        } else if (left >= SIZE || queue[left].heatLoss == -1) {
            queue[index] = queue[right];
            queue[right].heatLoss = -1;
            index = right;
        } else if (right >= SIZE || queue[right].heatLoss == -1) {
            queue[index] = queue[left];
            queue[left].heatLoss = -1;
            index = left;
        } else if (queue[left].heatLoss < queue[right].heatLoss) {
            queue[index] = queue[left];
            queue[left].heatLoss = -1;
            index = left;
        } else {
            queue[index] = queue[right];
            queue[right].heatLoss = -1;
            index = right;
        }
    }

    return node;
}
*/

heap_t *initHeap(void) {
	heap_t *heap = malloc(sizeof(*heap));
	heap->count = 0;
	heap->left = NULL;
	heap->right = NULL;
	return heap;
}

int minHeatLoss(grid_t grid) {
    int heatLoss = 0;
    bool *seen = malloc(4 * 4 * grid.sz * sizeof(*seen));
	heap_t *queue = initHeap();
    node_t node;
    node_t tmpNode;
    int key;
    int lookupKey;
    int nx;
    int ny;

    for (size_t i = 0; i < grid.sz * 4 * 4; ++i) {
        seen[i] = false;
    }

    // add node for right
    node.x = 1;
    node.y = 0;
    node.heatLoss = grid.cells[1] - '0';
    node.dir = right;
    node.steps = 1;

    heapPush(queue, node);

    // add node for down

    node.x = 0;
    node.y = 1;
    node.heatLoss = grid.cells[grid.width] - '0';
    node.dir = down;
    node.steps = 1;

    heapPush(queue, node);

    while (queue->count > 0) {
        node = heapPop(queue);
        // printf("(%d,%d,%d,%zu,%zu)\n", node.x, node.y, node.dir, node.steps,
        // queueCount);

        if (node.x == grid.width - 1 && node.y == grid.height - 1) {
            return node.heatLoss;
        }

        if (node.x < 0 || node.x >= grid.width || node.y < 0 ||
            node.y >= grid.height) {
            continue;
        }

        key = node.x + node.y * grid.width + node.steps * grid.sz +
              node.dir * 4 * grid.sz;
        // printf("(%d, %d, %zu, %d) = %d\n", node.x, node.y, node.steps,
        // node.dir, key);

        if (seen[key] || node.heatLoss == -1) {
            // printf("%c, %d\n", seen[key] ? 'T' : 'F', key);
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

        if (node.steps < 3 && 0 <= nx && nx < grid.width && 0 <= ny &&
            ny < grid.height) {
            seen[key] = true;
            lookupKey = ny * grid.width + nx;
            tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
            tmpNode.x = nx;
            tmpNode.y = ny;
            tmpNode.dir = node.dir;
            tmpNode.steps = node.steps + 1;
            heapPush(queue, tmpNode);
        }

        if (node.dir != up && node.dir != down) {
            if (node.y > 0) {
                lookupKey = (node.y - 1) * grid.width + node.x;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x;
                tmpNode.y = node.y - 1;
                tmpNode.dir = up;
                tmpNode.steps = 1;
                heapPush(queue, tmpNode);
            }

            if (node.y < grid.height - 1) {
                lookupKey = (node.y + 1) * grid.width + node.x;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x;
                tmpNode.y = node.y + 1;
                tmpNode.dir = down;
                tmpNode.steps = 1;
                heapPush(queue, tmpNode);
            }
        }

        if (node.dir != left && node.dir != right) {
            if (node.x > 0) {
                lookupKey = node.y * grid.width + node.x - 1;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x - 1;
                tmpNode.y = node.y;
                tmpNode.dir = left;
                tmpNode.steps = 1;
                heapPush(queue, tmpNode);
            }

            if (node.x < grid.width - 1) {
                lookupKey = node.y * grid.width + node.x + 1;
                tmpNode.heatLoss = node.heatLoss + grid.cells[lookupKey] - '0';
                tmpNode.x = node.x + 1;
                tmpNode.y = node.y;
                tmpNode.dir = right;
                tmpNode.steps = 1;
                heapPush(queue, tmpNode);
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
