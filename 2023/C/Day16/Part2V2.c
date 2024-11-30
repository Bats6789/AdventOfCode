/*
 * Name: Part2V2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Improved version of Part2 for Day 16.
 * Vers: 1.0.0 12/16/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef enum { left, right, up, down } dir_t;

typedef struct {
    int x;
    int y;
    dir_t dir;
} pt_t;

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

size_t getCount(const char *str, size_t sz, char c) {
    size_t count = 0;

    for (size_t i = 0; i < sz; ++i) {
        if (str[i] == c) {
            count++;
        }
    }

    return count;
}

int countTrue(bool *array, size_t sz) {
    int count = 0;

    for (size_t i = 0; i < sz; ++i) {
        count += array[i] ? 1 : 0;
    }

    return count;
}

int traverse(grid_t grid, pt_t pt) {
    bool *visited;
    pt_t queue[100];
    size_t queueCount = 0;
    size_t key;

    visited = malloc(sizeof(*visited) * grid.sz);

    for (size_t i = 0; i < grid.sz; ++i) {
        visited[i] = false;
    }

    queue[queueCount++] = pt;

    while (queueCount) {
        pt = queue[0];
        for (size_t i = 0; i < queueCount - 1; ++i) {
            queue[i] = queue[i + 1];
        }
        queueCount--;
        key = pt.y * grid.width + pt.x;

        if (!visited[key] ||
            (grid.cells[key] != '|' && grid.cells[key] != '-')) {
            switch (grid.cells[key]) {
                case '.':
                    switch (pt.dir) {
                        case left:
                            if (pt.x != 0) {
                                pt.x--;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case right:
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case down:
                            if (pt.y != grid.height - 1) {
                                pt.y++;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case up:
                            if (pt.y != 0) {
                                pt.y--;
                                queue[queueCount++] = pt;
                            }
                            break;
                    }
                    break;
                case '|':
                    switch (pt.dir) {
                        case left:
                            if (pt.y != 0) {
                                pt.y--;
                                pt.dir = up;
                                queue[queueCount++] = pt;
                                pt.y++;
                            }
                            if (pt.y != grid.height - 1) {
                                pt.y++;
                                pt.dir = down;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case right:
                            if (pt.y != 0) {
                                pt.y--;
                                pt.dir = up;
                                queue[queueCount++] = pt;
                                pt.y++;
                            }
                            if (pt.y != grid.height - 1) {
                                pt.y++;
                                pt.dir = down;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case down:
                            if (pt.y != grid.width - 1) {
                                pt.y++;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case up:
                            if (pt.y != 0) {
                                pt.y--;
                                queue[queueCount++] = pt;
                            }
                            break;
                    }
                    break;
                case '-':
                    switch (pt.dir) {
                        case left:
                            if (pt.x != 0) {
                                pt.x--;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case right:
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case down:
                            if (pt.x != 0) {
                                pt.x--;
                                pt.dir = left;
                                queue[queueCount++] = pt;
                                pt.x++;
                            }
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                pt.dir = right;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case up:
                            if (pt.x != 0) {
                                pt.x--;
                                pt.dir = left;
                                queue[queueCount++] = pt;
                                pt.x++;
                            }
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                pt.dir = right;
                                queue[queueCount++] = pt;
                            }
                            break;
                    }
                    break;
                case '/':
                    switch (pt.dir) {
                        case left:
                            if (pt.y != grid.height - 1) {
                                pt.y++;
                                pt.dir = down;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case right:
                            if (pt.y != 0) {
                                pt.y--;
                                pt.dir = up;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case down:
                            if (pt.x != 0) {
                                pt.x--;
                                pt.dir = left;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case up:
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                pt.dir = right;
                                queue[queueCount++] = pt;
                            }
                            break;
                    }
                    break;
                case '\\':
                    switch (pt.dir) {
                        case left:
                            if (pt.y != 0) {
                                pt.y--;
                                pt.dir = up;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case right:
                            if (pt.y != grid.height - 1) {
                                pt.y++;
                                pt.dir = down;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case down:
                            if (pt.x != grid.width - 1) {
                                pt.x++;
                                pt.dir = right;
                                queue[queueCount++] = pt;
                            }
                            break;
                        case up:
                            if (pt.x != 0) {
                                pt.x--;
                                pt.dir = left;
                                queue[queueCount++] = pt;
                            }
                            break;
                    }
                    break;
            }
            visited[key] = true;
        }
    }

    return countTrue(visited, grid.sz);
}

int maxLeft = 0;
int maxRight = 0;
int maxUp = 0;
int maxDown = 0;

void *leftThread(void *arg) {
	grid_t grid = *(grid_t *)arg;
	pt_t pt;
	int newCount;

	for (size_t i = 0; i < grid.height; ++i) {
		pt = (pt_t){grid.width - 1, i, left};
		newCount = traverse(grid, pt);
		maxLeft = newCount > maxLeft ? newCount : maxLeft;
	}

	pthread_exit(&maxLeft);
	return &maxLeft;
}

void *rightThread(void *arg) {
	grid_t grid = *(grid_t *)arg;
	pt_t pt;
	int newCount;

	for (size_t i = 0; i < grid.height; ++i) {
		pt = (pt_t){0, i, right};
		newCount = traverse(grid, pt);
		maxRight = newCount > maxRight ? newCount : maxRight;
	}

	pthread_exit(&maxRight);
	return &maxRight;
}

void *upThread(void *arg) {
	grid_t grid = *(grid_t *)arg;
	pt_t pt;
	int newCount;

	for (size_t i = 0; i < grid.width; ++i) {
		pt = (pt_t){i, grid.height - 1, up};
		newCount = traverse(grid, pt);
		maxUp = newCount > maxUp ? newCount : maxUp;
	}

	pthread_exit(&maxUp);
	return &maxUp;
}

void *downThread(void *arg) {
	grid_t grid = *(grid_t *)arg;
	pt_t pt;
	int newCount;

	for (size_t i = 0; i < grid.width; ++i) {
		pt = (pt_t){i, 0, down};
		newCount = traverse(grid, pt);
		maxDown = newCount > maxDown ? newCount : maxDown;
	}

	pthread_exit(&maxDown);
	return &maxDown;
}

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
	int maxCount = 0;
	pthread_t leftId;
	pthread_t rightId;
	pthread_t upId;
	pthread_t downId;

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

	// up and down
	pthread_create(&upId, NULL, &upThread, &grid);
	pthread_create(&downId, NULL, &downThread, &grid);
	// left and right
	pthread_create(&leftId, NULL, &leftThread, &grid);
	pthread_create(&rightId, NULL, &rightThread, &grid);

	pthread_join(upId, NULL);
	maxCount = maxUp > maxCount ? maxUp : maxCount;
	pthread_join(downId, NULL);
	maxCount = maxDown > maxCount ? maxDown : maxCount;
	pthread_join(leftId, NULL);
	maxCount = maxLeft > maxCount ? maxLeft : maxCount;
	pthread_join(rightId, NULL);
	maxCount = maxRight > maxCount ? maxRight : maxCount;

    printf("%d\n", maxCount);

    return EXIT_SUCCESS;
}
