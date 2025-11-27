/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 10 of AOC.
 * Vers: 1.0.0 12/10/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
    char *grid;
    size_t w;
    size_t h;
} grid_t;

bool *seen;

grid_t file_to_grid(FILE *file);
size_t walk(grid_t grid, size_t x, size_t y, char el);

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	size_t total = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	grid = file_to_grid(file);
	fclose(file);

	seen = malloc(sizeof *seen * grid.w * grid.h);

	for (size_t i = 0; i < grid.w * grid.h; ++i) {
		seen[i] = false;
	}

	for (size_t i = 0; i < grid.w; ++i) {
		for (size_t j = 0; j < grid.h; ++j) {
			if (grid.grid[i * grid.w + j] == '0') {
				for (size_t k = 0; k < grid.w * grid.h; ++k) {
					seen[k] = false;
				}
				total += walk(grid, j, i, '0');
			}
		}
	}

	free(grid.grid);
	free(seen);

	printf("%zu\n", total);

    return EXIT_SUCCESS;
}

grid_t file_to_grid(FILE *file) {
    grid_t grid = {NULL, 0, 0};
    char c;
    size_t col = 0;
    size_t row = 0;
	bool set_width = false;

    if (file == NULL) {
        return grid;
    }

    grid.h = 1000;
    grid.w = 1000;
    grid.grid = malloc(sizeof *grid.grid * grid.w * grid.h);

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            grid.grid[row++ * grid.w + col] = '\0';
			if (grid.w > col) {
				grid.w = col;
				grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);
				set_width = true;
			}
            col = 0;
        } else {
            grid.grid[row * grid.w + col++] = c;
        }

        if (col >= grid.w && !set_width) {
            grid.w += 1000;
            grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);
        }

        if (row >= grid.h) {
            grid.h += 1000;
            grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);
        }
    }

	grid.h = row;

	grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);

    return grid;
}

size_t walk(grid_t grid, size_t x, size_t y, char el) {
	size_t total = 0;

	if (el == '9') {
		if (!seen[y * grid.w + x]) {
			seen[y * grid.w + x] = true;
			return 1;
		} else {
			return 0;
		}
	}

	if (x > 0 && grid.grid[y * grid.w + x - 1] == el + 1) {
		total += walk(grid, x - 1, y, el + 1);
	}

	if (y > 0 && grid.grid[(y - 1) * grid.w + x] == el + 1) {
		total += walk(grid, x, y - 1, el + 1);
	}

	if (x < grid.w - 1 && grid.grid[y * grid.w + x + 1] == el + 1) {
		total += walk(grid, x + 1, y, el + 1);
	}

	if (y < grid.h - 1 && grid.grid[(y + 1) * grid.w + x] == el + 1) {
		total += walk(grid, x, y + 1, el + 1);
	}

	return total;
}
