/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 12 of AOC.
 * Vers: 1.0.0 12/12/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
    char *grid;
    size_t w;
    size_t h;
} grid_t;

typedef struct parameters {
	int perm;
	int area;
} parameters_t;

bool *seen = NULL;

grid_t file_to_grid(FILE *file);
parameters_t region(grid_t grid, int x, int y, char el);

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

	for (size_t i = 0; i < grid.w * grid.h; ++i) {
		if (!seen[i]) {
			div_t divide = div(i, grid.w);
			int x = divide.rem;
			int y = divide.quot;
			parameters_t res = region(grid, x, y, grid.grid[i]);
			total += res.perm * res.area;
		}
	}

	free(grid.grid);

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

parameters_t region(grid_t grid, int x, int y, char el) {
	parameters_t res = {0, 1};
	parameters_t walk_res;
	size_t index = y * grid.w + x;

	seen[index] = true;

	if (x > 0 && grid.grid[index - 1] == el && !seen[index - 1]) {
		walk_res = region(grid, x - 1, y, el);
		res.perm += walk_res.perm;
		res.area += walk_res.area;
	} else if (x == 0 || grid.grid[index - 1] != el) {
		res.perm += 1;
	}

	if (x < grid.w - 1 && grid.grid[index + 1] == el && !seen[index + 1]) {
		walk_res = region(grid, x + 1, y, el);
		res.perm += walk_res.perm;
		res.area += walk_res.area;
	} else if (x == grid.w - 1 || grid.grid[index + 1] != el) {
		res.perm += 1;
	}

	if (y > 0 && grid.grid[index - grid.w] == el && !seen[index - grid.w]) {
		walk_res = region(grid, x, y - 1, el);
		res.perm += walk_res.perm;
		res.area += walk_res.area;
	} else if (y == 0 || grid.grid[index - grid.w] != el) {
		res.perm += 1;
	}

	if (y < grid.h - 1 && grid.grid[index + grid.w] == el && !seen[index + grid.w]) {
		walk_res = region(grid, x, y + 1, el);
		res.perm += walk_res.perm;
		res.area += walk_res.area;
	} else if (y == grid.h - 1 || grid.grid[index + grid.w] != el) {
		res.perm += 1;
	}

	return res;
}
