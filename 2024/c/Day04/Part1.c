/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 4 of AOC.
 * Vers: 1.0.0 12/04/2024 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grid {
	char *grid;
	size_t w;
	size_t h;
} grid_t;

grid_t file_to_grid(FILE *file);
size_t count_str(grid_t grid, const char *s);

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	size_t count;

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

	count = count_str(grid, "XMAS");

	printf("%zu\n", count);

    return EXIT_SUCCESS;
}

grid_t file_to_grid(FILE *file) {
	grid_t grid = {NULL, 0, 0};
	char c;
	size_t col = 0;
	size_t row = 0;

	if (file == NULL) {
		return grid;
	}

	grid.h = 1000;
	grid.w = 1000;
	grid.grid = malloc(sizeof *grid.grid * grid.w * grid.h);

	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			grid.grid[row++ * grid.w + col] = '\0';
			col = 0;
		} else {
			grid.grid[row * grid.w + col++] = c;
		}

		if (col >= grid.w) {
			grid.w += 1000;
			grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);
		}

		if (row >= grid.h) {
			grid.h += 1000;
			grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);
		}
	}

	return grid;
}

size_t count_str(grid_t grid, const char *s) {
	size_t count = 0;
	char *tmp = NULL;
	size_t n = 0;

	if (s == NULL) {
		return count;
	}

	n = strlen(s);

	tmp = malloc(sizeof *tmp * (n + 1));

	for (size_t i = 0; i < grid.h * grid.w; ++i) {
		div_t res = div(i, grid.w);
		size_t x = res.rem;
		size_t y = res.quot;

		if (grid.grid[i] != s[0]) {
			continue;
		}

		// right
		if (x < grid.w - 3) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[y * grid.w + (x + j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// left
		if (x > 2) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[y * grid.w + (x - j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// up
		if (y > 2) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y - j) * grid.w + x];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// down
		if (y < grid.h - 3) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y + j) * grid.w + x];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// left up
		if (x > 2 && y > 2) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y - j) * grid.w + (x - j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// left down
		if (x > 2 && y < grid.h - 3) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y + j) * grid.w + (x - j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// right up
		if (x < grid.w - 3 && y > 2) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y - j) * grid.w + (x + j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}

		// right down
		if (x < grid.w - 3 && y < grid.h - 3) {
			for (size_t j = 0; j < 4; ++j) {
				tmp[j] = grid.grid[(y + j) * grid.w + (x + j)];
			}
			if (strncmp(s, tmp, n) == 0) {
				count++;
			}
		}
	}

	free(tmp);

	return count;
}
