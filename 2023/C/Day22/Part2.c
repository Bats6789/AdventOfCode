/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 22 of AOC.
 * Vers: 1.0.0 12/22/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1264

typedef struct {
    int *nodes;
    size_t sz;
    size_t cap;
} queue_t;

typedef struct {
    size_t *el;
    size_t sz;
    size_t cap;
} array_t;

typedef struct {
    int x;
    int y;
    int z;
} point_t;

typedef struct {
    point_t start;
    point_t stop;
} brick_t;

queue_t queueInit(void) {
    queue_t queue = {NULL, 0, 10};

    queue.nodes = malloc(sizeof(*queue.nodes) * queue.cap);

    return queue;
}

void enqueue(queue_t *queue, int node) {
    if (queue->sz >= queue->cap) {
        queue->cap *= 2;
        queue->nodes =
            realloc(queue->nodes, sizeof(*queue->nodes) * queue->cap);
    }

    queue->nodes[queue->sz++] = node;
}

int dequeu(queue_t *queue) {
    int node = queue->nodes[0];

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

point_t strToPoint(const char *str) {
    point_t pt;

    sscanf(str, "%d,%d,%d", &pt.x, &pt.y, &pt.z);

    return pt;
}

brick_t strToBrick(char *line) {
    brick_t brick;
    char *tok;

    tok = strtok(line, "~");

    brick.start = strToPoint(tok);

    tok = strtok(NULL, "~");

    brick.stop = strToPoint(tok);

    return brick;
}

int brickCmp(const void *l, const void *r) {
    brick_t left = *(brick_t *)l;
    brick_t right = *(brick_t *)r;

	if (left.start.z != right.start.z) {
		return left.start.z - right.start.z;
	} else if (left.start.y != right.start.y) {
		return left.start.y - right.start.y;
	} else {
		return left.start.x - right.start.x;
	}
}

static int inline max(int left, int right) {
    return left > right ? left : right;
}
static int inline min(int left, int right) {
    return left < right ? left : right;
}

bool overlap(brick_t left, brick_t right) {
    int maxStartX = max(left.start.x, right.start.x);
    int maxStartY = max(left.start.y, right.start.y);
    int minStopX = min(left.stop.x, right.stop.x);
    int minStopY = min(left.stop.y, right.stop.y);

    return maxStartX <= minStopX && maxStartY <= minStopY;
}

void addEl(array_t *array, int el) {
    if (!array) {
        return;
    }

    if (array->el == NULL || array->cap == 0) {
        array->cap = 10;
        array->el = malloc(sizeof(*array->el) * array->cap);
    }

    if (array->sz >= array->cap) {
        array->cap *= 2;
        array->el = realloc(array->el, sizeof(*array->el) * array->cap);
    }

    array->el[array->sz++] = el;
}

int getElAtIndex(array_t array, size_t i) {
    if (i >= array.sz) {
        return 0;
    }

    return array.el[i];
}

void clearArray(array_t *array) {
    free(array->el);
    array->el = NULL;
    array->sz = 0;
    array->cap = 0;
}

bool elInArray(int el, array_t array) {
    bool ans = false;

    for (size_t i = 0; i < array.sz && !ans; ++i) {
        if (array.el[i] == el) {
            ans = true;
        }
    }

    return ans;
}

void printArray(array_t array) {
    putchar('{');
    for (size_t i = 0; i < array.sz; ++i) {
        printf("%zu", array.el[i]);
        if (i + 1 != array.sz) {
            putchar(',');
            putchar(' ');
        }
    }
    putchar('}');
    putchar('\n');
}

int main(int argc, char **argv) {
    FILE *file;
    char *line;
    brick_t bricks[SIZE];
    size_t sz = 0;
    int maxZ;
    array_t supports[SIZE];
    array_t supported[SIZE];
    array_t falling = {NULL, 0, 0};
    queue_t q = queueInit();
    unsigned long long total = 0;

	memset(supports, 0, sizeof(*supports) * SIZE);
	memset(supported, 0, sizeof(*supported) * SIZE);

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while ((line = readLine(file)) != NULL) {
        bricks[sz++] = strToBrick(line);
    }

    qsort(bricks, sz, sizeof(*bricks), brickCmp);

    for (size_t i = 0; i < sz; ++i) {
        maxZ = 1;
        for (size_t j = 0; j < i; ++j) {
            if (overlap(bricks[i], bricks[j])) {
                maxZ = max(maxZ, bricks[j].stop.z + 1);
            }
        }
        bricks[i].stop.z -= bricks[i].start.z - maxZ;
        bricks[i].start.z = maxZ;
    }

    qsort(bricks, sz, sizeof(*bricks), brickCmp);

    for (size_t j = 0; j < sz; ++j) {
        for (size_t i = 0; i < j; ++i) {
            if (overlap(bricks[i], bricks[j]) &&
                bricks[i].stop.z + 1 == bricks[j].start.z) {
                addEl(supports + i, j);
                addEl(supported + j, i);
            }
        }
    }

    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < supports[i].sz; ++j) {
            size_t tmp = getElAtIndex(supports[i], j);
            if (supported[tmp].sz == 1) {
                enqueue(&q, tmp);
            }
        }

        for (size_t j = 0; j < q.sz; ++j) {
            addEl(&falling, q.nodes[j]);
        }
        addEl(&falling, i);

        while (q.sz) {
            int j = dequeu(&q);

            for (size_t k = 0; k < supports[j].sz; ++k) {
                bool addCurrentEl = true;
				int tmpIndex = getElAtIndex(supports[j], k);
                if (elInArray(tmpIndex, falling)) {
                    continue;
                }

                for (size_t l = 0; l < supported[tmpIndex].sz; ++l) {
                    if (!elInArray(getElAtIndex(supported[tmpIndex], l), falling)) {
                        addCurrentEl = false;
                    }
                }

                if (addCurrentEl) {
                    enqueue(&q, tmpIndex);
                    addEl(&falling, tmpIndex);
                }
            }
        }

        total += falling.sz - 1;

        clearArray(&falling);
    }

    printf("%llu\n", total);

    return EXIT_SUCCESS;
}
