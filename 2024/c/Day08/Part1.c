/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 8 of AOC.
 * Vers: 1.0.0 12/08/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct grid {
    char *grid;
    size_t w;
    size_t h;
} grid_t;

typedef struct point {
	int x;
	int y;
} point_t;

typedef struct array {
    point_t *data;
    size_t max;
    size_t sz;
} array_t;

grid_t file_to_grid(FILE *file);
bool inside(point_t pt, point_t d, point_t boundary);
array_t init_array(void);
void append_array(array_t *array, point_t el);
point_t get_array(array_t array, size_t index);

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	char unique_items[256];
	size_t uniq_sz = 0;
	bool found = false;
	point_t pt;
	point_t pt2;
	point_t d;
	point_t boundary;
	array_t points[256];
	size_t count = 0;

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

	boundary.x = grid.w;
	boundary.y = grid.h;

	// find unique elements
	for (size_t i = 0; i < grid.w * grid.h; ++i) {
		if (grid.grid[i] == '.') {
			continue;
		}
		found = false;
		for (size_t j = 0; j < uniq_sz && !found; ++j) {
			if (unique_items[j] == grid.grid[i]) {
				found = true;
			}
		}

		if (!found) {
			unique_items[uniq_sz++] = grid.grid[i];
		}
	}

	// gather points for unique elements
	for (size_t i = 0; i < uniq_sz; ++i) {
		points[i] = init_array();

		for (size_t j = 0; j < grid.w * grid.h; ++j) {
			if (grid.grid[j] == unique_items[i]) {
				div_t res = div(j, grid.w);
				pt.x = res.rem;
				pt.y = res.quot;
				append_array(points + i, pt);
			}
		}
	}

	// collect anti-nodes
	for (size_t i = 0; i < uniq_sz; ++i) {
		array_t point_set = points[i];

		for (size_t j = 0; j < point_set.sz - 1; ++j) {
			pt = point_set.data[j];
			for (size_t k = j + 1; k < point_set.sz; ++k) {
				pt2 = point_set.data[k];

				d.x = pt.x - pt2.x;
				d.y = pt.y - pt2.y;
				size_t tmp = (pt.y + d.y) * grid.w + (pt.x + d.x);

				if (inside(pt, d, boundary) && grid.grid[tmp] != '#') {
					grid.grid[tmp] = '#';
					count += 1;
				}

				d.x *= -1;
				d.y *= -1;
				tmp = (pt2.y + d.y) * grid.w + (pt2.x + d.x);

				if (inside(pt2, d, boundary) && grid.grid[tmp] != '#') {
					grid.grid[tmp] = '#';
					count += 1;
				}
			}
		}
	}

	// free
	for (size_t i = 0; i < uniq_sz; ++i) {
		free(points[i].data);
		points[i].sz = 0;
		points[i].max = 0;
	}

	free(grid.grid);

	printf("%zu\n", count);

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

inline bool inside(point_t pt, point_t d, point_t boundary) {
	return 0 <= pt.x + d.x && pt.x + d.x < boundary.x && 0 <= pt.y + d.y && pt.y + d.y < boundary.y;
}

array_t init_array(void) {
    array_t array;

    array.max = 100;
    array.sz = 0;

    array.data = malloc(sizeof *array.data * array.max);

    return array;
}

void append_array(array_t *array, point_t el) {
    if (array == NULL) {
        return;
    }

    if (array->sz >= array->max) {
        array->max *= 2;
        array->data = realloc(array->data, sizeof *array->data * array->max);
    }

    array->data[array->sz++] = el;
}

point_t get_array(array_t array, size_t index) {
    if (index >= array.sz) {
        return (point_t){-1, -1};
    }

    return array.data[index];
}
