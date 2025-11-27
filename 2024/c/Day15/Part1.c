/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 15 of AOC.
 * Vers: 1.0.0 12/15/2024 CBW - Original code.
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

typedef struct shift {
	point_t to;
	point_t from;
} shift_t;

typedef struct array {
    shift_t *data;
    size_t max;
    size_t sz;
} array_t;

grid_t file_to_grid(FILE *file);
array_t init_array(void);
void append_array(array_t *array, shift_t el);
void insert_array(array_t *array, shift_t el, size_t i);
shift_t get_array(array_t array, size_t index);
bool point_equal(point_t left, point_t right);
bool shift_equal(shift_t left, shift_t right);
bool in_array(array_t array, shift_t el);
bool get_shifts(grid_t grid, point_t pos, point_t d, array_t *shift_list);

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
	char move;
	array_t shift_list = init_array();
	point_t pos;
	point_t d;
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

	for (int y = 0; y < grid.h; ++y) {
		for (int x = 0; x < grid.w; ++x) {
			if (grid.grid[y * grid.w + x] == '@') {
				pos.x = x;
				pos.y = y;
			}
		}
	}

	while ((move = fgetc(file)) != EOF) {
		shift_list.sz = 0; // 'clear' list at each move

		switch (move) {
			case '^':
				d.x = 0;
				d.y = -1;
				if (get_shifts(grid, pos, d, &shift_list)) {
					for (size_t i = 0; i < shift_list.sz; ++i) {
						point_t to = shift_list.data[i].to;
						point_t from = shift_list.data[i].from;

						size_t to_i = to.y * grid.w + to.x;
						size_t from_i = from.y * grid.w + from.x;

						grid.grid[to_i] = grid.grid[from_i];
						grid.grid[from_i] = '.';
					}

					grid.grid[pos.y * grid.w + pos.x] = '.';
					pos.y += d.y;
					grid.grid[pos.y * grid.w + pos.x] = '@';
				}
				break;
			case '<':
				d.x = -1;
				d.y = 0;
				if (get_shifts(grid, pos, d, &shift_list)) {
					for (size_t i = 0; i < shift_list.sz; ++i) {
						point_t to = shift_list.data[i].to;
						point_t from = shift_list.data[i].from;

						size_t to_i = to.y * grid.w + to.x;
						size_t from_i = from.y * grid.w + from.x;

						grid.grid[to_i] = grid.grid[from_i];
						grid.grid[from_i] = '.';
					}

					grid.grid[pos.y * grid.w + pos.x] = '.';
					pos.x += d.x;
					grid.grid[pos.y * grid.w + pos.x] = '@';
				}
				break;
			case '>':
				d.x = 1;
				d.y = 0;
				if (get_shifts(grid, pos, d, &shift_list)) {
					for (size_t i = 0; i < shift_list.sz; ++i) {
						point_t to = shift_list.data[i].to;
						point_t from = shift_list.data[i].from;

						size_t to_i = to.y * grid.w + to.x;
						size_t from_i = from.y * grid.w + from.x;

						grid.grid[to_i] = grid.grid[from_i];
						grid.grid[from_i] = '.';
					}

					grid.grid[pos.y * grid.w + pos.x] = '.';
					pos.x += d.x;
					grid.grid[pos.y * grid.w + pos.x] = '@';
				}
				break;
			case 'v':
				d.x = 0;
				d.y = 1;
				if (get_shifts(grid, pos, d, &shift_list)) {
					for (size_t i = 0; i < shift_list.sz; ++i) {
						point_t to = shift_list.data[i].to;
						point_t from = shift_list.data[i].from;

						size_t to_i = to.y * grid.w + to.x;
						size_t from_i = from.y * grid.w + from.x;

						grid.grid[to_i] = grid.grid[from_i];
						grid.grid[from_i] = '.';
					}

					grid.grid[pos.y * grid.w + pos.x] = '.';
					pos.y += d.y;
					grid.grid[pos.y * grid.w + pos.x] = '@';
				}
				break;
			case '\n':
				// skip
				break;
			default:
				fputs("ERROR: Should never happen\n", stderr);
				return EXIT_FAILURE;
				break;
		}
	}

	for (int y = 0; y < grid.h; ++y) {
		for (int x = 0; x < grid.w; ++x) {
			if (grid.grid[y * grid.w + x] == 'O') {
				total += 100 * y + x;
			}
		}
	}

	printf("%zu\n", total);

    fclose(file);
    free(grid.grid);
	free(shift_list.data);

    return EXIT_SUCCESS;
}

grid_t file_to_grid(FILE *file) {
    grid_t grid = {NULL, 0, 0};
    char c;
    char prev = '\0';
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
        if (c == '\n' && prev == '\n') {
            break;
        }

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
        prev = c;
    }

    grid.h = row;

    grid.grid = realloc(grid.grid, sizeof *grid.grid * grid.w * grid.h);

    return grid;
}

array_t init_array(void) {
    array_t array;

    array.max = 100;
    array.sz = 0;

    array.data = malloc(sizeof *array.data * array.max);

    return array;
}

void append_array(array_t *array, shift_t el) {
    if (array == NULL) {
        return;
    }

    if (array->sz >= array->max) {
        array->max *= 2;
        array->data = realloc(array->data, sizeof *array->data * array->max);
    }

    array->data[array->sz++] = el;
}

void insert_array(array_t *array, shift_t el, size_t index) {
    if (array == NULL || index >= array->sz) {
        return;
    }

    if (array->sz + 1 >= array->max) {
        array->max *= 2;
        array->data = realloc(array->data, sizeof *array->data * array->max);
    }

    for (ssize_t i = array->sz; i > index; --i) {
        array->data[i] = array->data[i - 1];
    }

    array->data[index] = el;

    array->sz += 1;
}

shift_t get_array(array_t array, size_t index) {
    if (index >= array.sz) {
        return (shift_t){-1, -1};
    }

    return array.data[index];
}

bool point_equal(point_t left, point_t right) {
	return left.x == right.x && left.y == right.y;
}

bool shift_equal(shift_t left, shift_t right) {
	return point_equal(left.to, right.to) && point_equal(left.from, right.from);
}

bool in_array(array_t array, shift_t el) {
	for (size_t i = 0; i < array.sz; ++i) {
		if (shift_equal(array.data[i], el)) {
			return true;
		}
	}
	return false;
}

bool get_shifts(grid_t grid, point_t pos, point_t d, array_t *shift_list) {
	point_t new_point = {pos.x + d.x, pos.y + d.y};
	if (grid.grid[pos.y * grid.w + pos.x] == '.') {
		return true;
	} else if (grid.grid[pos.y * grid.w + pos.x] == '#') {
		return false;
	} else if (get_shifts(grid, new_point, d, shift_list)) {
		shift_t shift = {new_point, pos};
		if (!in_array(*shift_list, shift)) {
			append_array(shift_list, shift);
		}
		return true;
	} else {
		return false;
	}
}
