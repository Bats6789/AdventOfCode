/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 6 of AOC.
 * Vers: 1.0.0 12/06/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum dir { up, down, left, right } dir_t;

typedef struct grid {
    char *grid;
    size_t w;
    size_t h;
} grid_t;

typedef struct point {
    int x;
    int y;
} point_t;

typedef struct state {
    point_t pt;
    dir_t dir;
} state_t;

grid_t file_to_grid(FILE *file);
bool passed(grid_t grid, point_t point);

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
    point_t point;
    point_t start;
    size_t count = 0;
    dir_t dir = up;

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

    for (size_t i = 0; i < grid.w * grid.h; ++i) {
        if (grid.grid[i] == '^') {
            div_t res = div(i, grid.w);
            point.x = res.rem;
            point.y = res.quot;
            start = point;
            break;
        }
    }

    while (grid.w > point.x && point.x >= 0 && grid.h > point.y && point.y >= 0) {
        if (grid.grid[point.y * grid.w + point.x] == '.') {
            grid.grid[point.y * grid.w + point.x] = 'X';
        }

        switch (dir) {
            case up:
                if (point.y > 0 && grid.grid[(point.y - 1) * grid.w + point.x] == '#') {
                    dir = right;
                } else {
                    point.y--;
                }
                break;
            case down:
                if (point.y < grid.h - 1 && grid.grid[(point.y + 1) * grid.w + point.x] == '#') {
                    dir = left;
                } else {
                    point.y++;
                }
                break;
            case left:
                if (point.x > 0 && grid.grid[point.y * grid.w + point.x - 1] == '#') {
                    dir = up;
                } else {
                    point.x--;
                }
                break;
            case right:
                if (point.x < grid.w - 1 && grid.grid[point.y * grid.w + point.x + 1] == '#') {
                    dir = down;
                } else {
                    point.x++;
                }
                break;
        }
    }

    for (size_t i = 0; i < grid.h * grid.w; ++i) {
        if (grid.grid[i] == 'X') {
            grid.grid[i] = '#';
            if (passed(grid, start)) {
                count++;
            }
            grid.grid[i] = 'X';
        }
    }

    printf("%zu\n", count);

    return EXIT_SUCCESS;
}

static inline bool equal(state_t s1, state_t s2) { return s1.pt.x == s2.pt.x && s1.pt.y == s2.pt.y && s1.dir == s2.dir; }

bool in(state_t *set, state_t state, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        if (equal(set[i], state)) {
            return true;
        }
    }

    return false;
}

bool passed(grid_t grid, point_t point) {
    dir_t dir = up;
    state_t *set = NULL;
	state_t state;
    size_t set_max = 1000;
    size_t set_sz = 0;

    set = malloc(sizeof *set * set_max);

    while (grid.w > point.x && point.x >= 0 && grid.h > point.y && point.y >= 0) {
        if (grid.grid[point.y * grid.w + point.x] == '.') {
            grid.grid[point.y * grid.w + point.x] = 'X';
        }

        switch (dir) {
            case up:
                if (point.y > 0 && grid.grid[(point.y - 1) * grid.w + point.x] == '#') {
					state.pt = point;
					state.dir = dir;
					if (in(set, state, set_sz)) {
						return true;
					} else {
						set[set_sz++] = state;

						if (set_sz >= set_max) {
							set_max += 100;
							set = realloc(set, sizeof *set * set_max);
						}
					}
                    dir = right;
                } else {
                    point.y--;
                }
                break;
            case down:
                if (point.y < grid.h - 1 && grid.grid[(point.y + 1) * grid.w + point.x] == '#') {
					state.pt = point;
					state.dir = dir;
					if (in(set, state, set_sz)) {
						return true;
					} else {
						set[set_sz++] = state;

						if (set_sz >= set_max) {
							set_max += 100;
							set = realloc(set, sizeof *set * set_max);
						}
					}
                    dir = left;
                } else {
                    point.y++;
                }
                break;
            case left:
                if (point.x > 0 && grid.grid[point.y * grid.w + point.x - 1] == '#') {
					state.pt = point;
					state.dir = dir;
					if (in(set, state, set_sz)) {
						return true;
					} else {
						set[set_sz++] = state;

						if (set_sz >= set_max) {
							set_max += 100;
							set = realloc(set, sizeof *set * set_max);
						}
					}
                    dir = up;
                } else {
                    point.x--;
                }
                break;
            case right:
                if (point.x < grid.w - 1 && grid.grid[point.y * grid.w + point.x + 1] == '#') {
					state.pt = point;
					state.dir = dir;
					if (in(set, state, set_sz)) {
						return true;
					} else {
						set[set_sz++] = state;

						if (set_sz >= set_max) {
							set_max += 100;
							set = realloc(set, sizeof *set * set_max);
						}
					}
                    dir = down;
                } else {
                    point.x++;
                }
                break;
        }
    }
    return false;
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
