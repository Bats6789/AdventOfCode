/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 4 of AOC.
 * Vers: 1.0.0 12/04/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
    char *grid;
    size_t w;
    size_t max_w;
    size_t h;
    size_t max_h;
} grid_t;

static inline char grid_get(grid_t grid, size_t row, size_t col) { return grid.grid[row * grid.max_w + col]; }

grid_t file_to_grid(FILE *file);
unsigned int adjacent(grid_t grid, size_t row, size_t col);

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
    unsigned int count = 0;

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

    for (size_t row = 0; row < grid.h; ++row) {
        for (size_t col = 0; col < grid.w; ++col) {
            if (grid_get(grid, row, col) == '@' && adjacent(grid, row, col) < 4) {
                count += 1;
            }
        }
    }

    printf("%u\n", count);

    return EXIT_SUCCESS;
}

grid_t file_to_grid(FILE *file) {
    grid_t grid = {NULL, 0, 0, 0, 0};
    char c;
	size_t col = 0;

    if (file == NULL) {
        return grid;
    }

    grid.max_h = 1000;
    grid.max_w = 1000;
    grid.grid = malloc(sizeof *grid.grid * grid.max_w * grid.max_h);

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            grid.grid[grid.h++ * grid.max_w + col] = '\0';
			grid.w = col > grid.w ? col : grid.w;
			col = 0;
        } else {
            grid.grid[grid.h * grid.max_w + col++] = c;
        }

        if (col >= grid.max_w) {
            grid.max_w += 1000;
            grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.max_w * grid.max_h);
        }

        if (grid.h >= grid.max_h) {
            grid.max_h += 1000;
            grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.max_w * grid.max_h);
        }
    }

    return grid;
}

unsigned int adjacent(grid_t grid, size_t row, size_t col) {
    unsigned int count = 0;

    if (row > 0) {
        if (col > 0 && grid_get(grid, row - 1, col - 1) == '@') {
            count += 1;
        }
        if (grid_get(grid, row - 1, col) == '@') {
            count += 1;
        }
        if (col < grid.w - 1 && grid_get(grid, row - 1, col + 1) == '@') {
            count += 1;
        }
    }

    if (col > 0 && grid_get(grid, row, col - 1) == '@') {
        count += 1;
    }
    if (col < grid.w - 1 && grid_get(grid, row, col + 1) == '@') {
        count += 1;
    }

    if (row < grid.h - 1) {
        if (col > 0 && grid_get(grid, row + 1, col - 1) == '@') {
            count += 1;
        }
        if (grid_get(grid, row + 1, col) == '@') {
            count += 1;
        }
        if (col < grid.w - 1 && grid_get(grid, row + 1, col + 1) == '@') {
            count += 1;
        }
    }

    return count;
}
