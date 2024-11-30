/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 14 of AOC.
 * Vers: 1.0.0 12/14/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

unsigned long long getScore(grid_t grid) {
	unsigned long long ans = 0;

	for (size_t i = 0; i < grid.height; ++i) {
		ans += (grid.height - i) * getCount(grid.cells + i * grid.width, grid.width, 'O');
	}

	return ans;
}

void pushUp(grid_t grid, size_t i, size_t j) {
	bool done = false;
	char tmp;

	while (!done) {
		if (i == 0 || grid.cells[(i - 1) * grid.width + j] != '.') {
			done = true;
		} else {
			tmp = grid.cells[i * grid.width + j];
			grid.cells[i * grid.width + j] = grid.cells[(i - 1) * grid.width + j];
			grid.cells[--i * grid.width + j] = tmp;
		}
	}
}

void pushDown(grid_t grid, size_t i, size_t j) {
	bool done = false;
	char tmp;

	while (!done) {
		if (i == grid.height - 1 || grid.cells[(i + 1) * grid.width + j] != '.') {
			done = true;
		} else {
			tmp = grid.cells[i * grid.width + j];
			grid.cells[i * grid.width + j] = grid.cells[(i + 1) * grid.width + j];
			grid.cells[++i * grid.width + j] = tmp;
		}
	}
}

void pushLeft(grid_t grid, size_t i, size_t j) {
	bool done = false;
	char tmp;

	while (!done) {
		if (j == 0 || grid.cells[i * grid.width + j - 1] != '.') {
			done = true;
		} else {
			tmp = grid.cells[i * grid.width + j];
			grid.cells[i * grid.width + j] = grid.cells[i * grid.width + j - 1];
			grid.cells[i * grid.width + --j] = tmp;
		}
	}
}

void pushRight(grid_t grid, size_t i, size_t j) {
	bool done = false;
	char tmp;

	while (!done) {
		if (j == grid.width - 1 || grid.cells[i * grid.width + j + 1] != '.') {
			done = true;
		} else {
			tmp = grid.cells[i * grid.width + j];
			grid.cells[i * grid.width + j] = grid.cells[i * grid.width + j + 1];
			grid.cells[i * grid.width + ++j] = tmp;
		}
	}
}

void cycle(grid_t grid) {
	// north
	for (size_t i = 1; i < grid.height; ++i) {
		for (size_t j = 0; j < grid.width; ++j) {
			if (grid.cells[i * grid.width + j] == 'O') {
				pushUp(grid, i, j);
			}
		}
	}

	// west
	for (size_t i = 0; i < grid.height; ++i) {
		for (size_t j = 1; j < grid.width; ++j) {
			if (grid.cells[i * grid.width + j] == 'O') {
				pushLeft(grid, i, j);
			}
		}
	}

	// south
	for (ssize_t i = grid.height - 2; i >= 0; --i) {
		for (size_t j = 0; j < grid.width; ++j) {
			if (grid.cells[i * grid.width + j] == 'O') {
				pushDown(grid, i, j);
			}
		}
	}

	// east
	for (size_t i = 0; i < grid.height; ++i) {
		for (ssize_t j = grid.width - 2; j >= 0; --j) {
			if (grid.cells[i * grid.width + j] == 'O') {
				pushRight(grid, i, j);
			}
		}
	}
}

grid_t copyGrid(grid_t grid) {
	grid_t copy;

	copy.cells = malloc(sizeof(*copy.cells) * grid.sz);
	memcpy(copy.cells, grid.cells, sizeof(*copy.cells) * grid.sz);
	copy.width = grid.width;
	copy.height = grid.height;
	copy.sz = grid.sz;

	return copy;
}

int main(int argc, char **argv) {
    FILE *file = NULL;
	grid_t grid = {0, 0, 0};
	grid_t *cache = NULL;
	size_t loop = 0;
	size_t first = 0;
	size_t cacheSize = 100;
	bool done = false;

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

	cache = malloc(sizeof(*cache) * cacheSize);

	cache[loop] = copyGrid(grid);
	for (loop = 1; loop <= 1000000000 && !done; loop++) {

		cycle(grid);
		for (first = 0; first < loop && !done; ++first) {
			if (strncmp(cache[first].cells, grid.cells, grid.sz) == 0) {
				done = true;
			}
		}

		if (!done) {
			if (loop == cacheSize) {
				cacheSize *= 2;
				cache = realloc(cache, sizeof(*cache) * cacheSize);
			}

			cache[loop] = copyGrid(grid);
		}
	}

	printf("%llu\n", getScore(cache[(1000000000 - first) % (loop - first) + first]));

    return EXIT_SUCCESS;
}
