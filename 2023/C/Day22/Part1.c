/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 22 of AOC.
 * Vers: 1.0.0 12/22/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1263

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

    return left.start.z - right.start.z;
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
	if (!array) { return; }

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

int getElAtIndex(array_t array, size_t i) {
	if (i >= array.sz) {
		return 0;
	}

	return array.el[i];
}

int main(int argc, char **argv) {
    FILE *file;
    char *line;
    brick_t bricks[SIZE];
    size_t sz = 0;
    int maxZ;
    array_t supports[SIZE] = {0};
    array_t supported[SIZE] = {0};
    unsigned long long total = 0;

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
		bool canDelete = true;

		for (size_t j = 0; j < supports[i].sz && canDelete; ++j) {
			if (supported[getElAtIndex(supports[i], j)].sz < 2) {
				canDelete = false;
			}
		}

		if (canDelete) {
			total++;
		}
	}

    printf("%llu\n", total);

    return EXIT_SUCCESS;
}
