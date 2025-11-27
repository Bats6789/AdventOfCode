/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 20 of AOC.
 * Vers: 1.0.0 12/20/2024 CBW - Original code.
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

grid_t file_to_grid(FILE *file);
bool point_equal(point_t left, point_t right);

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	point_t start;
	point_t stop;
	point_t loc;
	size_t count = 0;
	ssize_t *dist = NULL;

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

	for (int y = 0; y < grid.h; ++y) {
		for (int x = 0; x < grid.w; ++x) {
			if (grid.grid[y * grid.w + x] == 'S'){
				start.x = x;
				start.y = y;
			} else if (grid.grid[y * grid.w + x] == 'E'){
				stop.x = x;
				stop.y = y;
			}
		}
	}

	dist = malloc(sizeof *dist * grid.w * grid.h);
	for (size_t i = 0; i < grid.w * grid.h; ++i) {
		dist[i] = -1;
	}

	dist[start.y * grid.w + start.x] = 0;

	loc = start;

	// get depth
	while (!point_equal(loc, stop)) {
		size_t tmp = loc.y * grid.w + loc.x - 1;
		if (loc.x > 0 && grid.grid[tmp] != '#' && dist[tmp] == -1) {
			loc.x -= 1;
			dist[tmp] = dist[tmp + 1] + 1;
		}

		tmp = loc.y * grid.w + loc.x + 1;
		if (loc.x < grid.w - 1 && grid.grid[tmp] != '#' && dist[tmp] == -1) {
			loc.x += 1;
			dist[tmp] = dist[tmp - 1] + 1;
		}

		tmp = (loc.y - 1) * grid.w + loc.x;
		if (loc.y > 0 && grid.grid[tmp] != '#' && dist[tmp] == -1) {
			loc.y -= 1;
			dist[tmp] = dist[tmp + grid.w] + 1;
		}

		tmp = (loc.y + 1) * grid.w + loc.x;
		if (loc.x < grid.w - 1 && grid.grid[tmp] != '#' && dist[tmp] == -1) {
			loc.y += 1;
			dist[tmp] = dist[tmp - grid.w] + 1;
		}
	}

	for (point_t walk = {0, 0}; walk.y < grid.h; ++walk.y) {
		for (walk.x = 0; walk.x < grid.w; ++walk.x) {
			ssize_t from_i = walk.y * grid.w + walk.x;
			if (grid.grid[from_i] == '#') {
				continue;
			}

			for (ssize_t radius = 2; radius <= 20; ++radius) {
				for (int dr = 0; dr <= radius; ++dr) {
					point_t to = walk;
					int dc = radius - dr;

					to.x -= dc;
					to.y -= dr;
					ssize_t to_i = to.y * grid.w + to.x;
					if (to.x > 0 && to.y > 0
						&& grid.grid[to_i] != '#'
						&& dist[from_i] - dist[to_i] >= 100 + radius) {
						count += 1;
					}

					to = walk;
					to.x += dc;
					to.y -= dr;
					to_i = to.y * grid.w + to.x;
					if (to.x < grid.w - 1 && to.y > 0
						&& grid.grid[to_i] != '#'
						&& dist[from_i] - dist[to_i] >= 100 + radius
						&& dc != 0) {
						count += 1;
					}

					to = walk;
					to.x -= dc;
					to.y += dr;
					to_i = to.y * grid.w + to.x;
					if (to.x > 0 && to.y < grid.h - 1
						&& grid.grid[to_i] != '#'
						&& dist[from_i] - dist[to_i] >= 100 + radius
						&& dr != 0) {
						count += 1;
					}

					to = walk;
					to.x += dc;
					to.y += dr;
					to_i = to.y * grid.w + to.x;
					if (to.x < grid.w - 1 && to.y < grid.h - 1
						&& grid.grid[to_i] != '#'
						&& dist[from_i] - dist[to_i] >= 100 + radius
						&& dr != 0 && dc != 0) {
						count += 1;
					}
				}
			}
		}
	}

	printf("%zu\n", count);

	free(dist);
	free(grid.grid);

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
			row++;
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

inline bool point_equal(point_t left, point_t right) {
	return left.x == right.x && left.y == right.y;
}
