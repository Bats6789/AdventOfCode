/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 14 of AOC.
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

	for (size_t i = 1; i < grid.height; ++i) {
		for (size_t j = 0; j < grid.width; ++j) {
			if (grid.cells[i * grid.width + j] == 'O') {
				pushUp(grid, i, j);
			}
		}
	}

	printf("%llu\n", getScore(grid));

    return EXIT_SUCCESS;
}
