/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 16 of AOC.
 * Vers: 1.0.0 12/16/2024 CBW - Original code.
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

typedef enum dir {
	left, up, right, down
} dir_t;

typedef struct node {
	size_t score;
	point_t pt;
	dir_t dir;
} node_t;

typedef struct heapq {
	node_t *data;
	size_t sz;
	size_t max;
} heapq_t;

typedef struct item {
	point_t pt;
	dir_t dir;
} item_t;

typedef struct set {
	item_t *data;
	size_t sz;
	size_t max;
} set_t;

grid_t file_to_grid(FILE *file);
set_t init_set(void);
heapq_t init_queue(void);
size_t parent(size_t i);
size_t left_child(size_t i);
size_t right_child(size_t i);
void shift_down(heapq_t *q, size_t i);
void shift_up(heapq_t *q, size_t i);
node_t pop_queue(heapq_t *q);
void push_queue(heapq_t *q, node_t el);
bool in_set(set_t s, item_t el);
void insert_set(set_t *s, item_t el);
int cmp_node(node_t a, node_t b);
bool item_equal(item_t a, item_t b);
bool point_equal(point_t left, point_t right);

int main(int argc, char **argv) {
    FILE *file;
	grid_t grid;
	point_t start;
	point_t end;
	point_t loc;
	dir_t dir = right;
	node_t node;
	item_t item;
	heapq_t pq = init_queue();
	set_t set = init_set();
	size_t current_score;

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

	for (size_t y = 0; y < grid.h; ++y) {
		for (size_t x = 0; x < grid.w; ++x) {
			if (grid.grid[y * grid.w + x] == 'S') {
				start.x = x;
				start.y = y;
			} else if (grid.grid[y * grid.w + x] == 'E') {
				end.x = x;
				end.y = y;
			}
		}
	}

	loc = start;
	item.pt = start;
	item.dir = dir;
	node.pt = start;
	node.dir = dir;

	node.score = 1;
	node.pt.x = start.x + 1;

	if (grid.grid[node.pt.y * grid.w + node.pt.x] != '#') {
		push_queue(&pq, node);
	}

	node.pt.x = start.x;
	node.dir = up;
	node.score = 1000;
	push_queue(&pq, node);

	while (!point_equal(loc, end) && pq.sz != 0) {
		node = pop_queue(&pq);
		loc = node.pt;
		dir = node.dir;
		current_score = node.score;

		if (point_equal(loc, end)) {
			break;
		}

		item.pt = loc;
		item.dir = dir;
		insert_set(&set, item);

		switch (dir) {
			case right:
				item.pt.x += 1;
				if (!in_set(set, item) && item.pt.x < grid.w &&
					grid.grid[item.pt.y * grid.w + item.pt.x] != '#') {
					node.score = current_score + 1;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.pt.x = loc.x;
				item.dir = up;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.dir = down;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				break;
			case left:
				item.pt.x -= 1;
				if (!in_set(set, item) && item.pt.x > 0 &&
					grid.grid[item.pt.y * grid.w + item.pt.x] != '#') {
					node.score = current_score + 1;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.pt.x = loc.x;
				item.dir = up;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.dir = down;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				break;
			case down:
				item.pt.y += 1;
				if (!in_set(set, item) && item.pt.y < grid.h &&
					grid.grid[item.pt.y * grid.w + item.pt.x] != '#') {
					node.score = current_score + 1;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.pt.y = loc.y;
				item.dir = right;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.dir = left;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				break;
			case up:
				item.pt.y -= 1;
				if (!in_set(set, item) && item.pt.y > 0 &&
					grid.grid[item.pt.y * grid.w + item.pt.x] != '#') {
					node.score = current_score + 1;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.pt.y = loc.y;
				item.dir = right;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
				item.dir = left;
				if (!in_set(set, item)) {
					node.score = current_score + 1000;
					node.dir = item.dir;
					node.pt = item.pt;
					push_queue(&pq, node);
				}
			  break;
		}
	}

	printf("%zu\n", current_score);

	free(grid.grid);
	free(pq.data);
	free(set.data);

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

set_t init_set(void) {
	set_t s = {NULL, 0, 100};

	s.data = malloc(sizeof *s.data * s.max);

	return s;
}

heapq_t init_queue(void) {
	heapq_t q = {NULL, 0, 100};

	q.data = malloc(sizeof *q.data * q.max);

	return q;
}


inline size_t parent(size_t i) { return (i - 1) / 2; }
inline size_t left_child(size_t i) {return (2 * i) + 1;}
inline size_t right_child(size_t i) {return (2 * i) + 2;}

void shift_down(heapq_t *q, size_t i) {
	size_t min_index = i;
	size_t left = left_child(i);
	size_t right = right_child(i);

	if (left <= q->sz && cmp_node(q->data[left], q->data[min_index]) < 0) {
		min_index = left;
	}

	if (right <= q->sz && cmp_node(q->data[right], q->data[min_index]) < 0) {
		min_index = right;
	}

	if (i != min_index) {
		node_t tmp = q->data[min_index];
		q->data[min_index] = q->data[i];
		q->data[i] = tmp;

		shift_down(q, min_index);
	}
}

void shift_up(heapq_t *q, size_t i) {
	while (i > 0 && cmp_node(q->data[parent(i)], q->data[i]) > 0) {
		node_t tmp = q->data[parent(i)];
		q->data[parent(i)] = q->data[i];
		q->data[i] = tmp;

		i = parent(i);
	}
}

node_t pop_queue(heapq_t *q) {
	if (q == NULL || q->sz == 0) {
		return (node_t){0, {-1, -1}, up};
	}

	node_t node = q->data[0];

	q->data[0] = q->data[--q->sz];

	if (q->sz == 0) {
		return node;
	}

	shift_down(q, 0);

	return node;
}

void push_queue(heapq_t *q, node_t node) {
	q->data[q->sz++] = node;

	if (q->sz >= q->max) {
		q->max *= 2;
		q->data = realloc(q->data, sizeof *q->data * q->max);
	}

	shift_up(q, q->sz - 1);
}

bool in_set(set_t s, item_t el) {
	for (size_t i = 0; i < s.sz; ++i) {
		if (item_equal(s.data[i], el)) {
			return true;
		}
	}
	return false;
}

void insert_set(set_t *s, item_t el) {
	if (in_set(*s, el)) {
		return;
	}

	s->data[s->sz++] = el;

	if (s->sz >= s->max) {
		s->max *= 2;
		s->data = realloc(s->data, sizeof *s->data * s->max);
	}
}

int cmp_node(node_t a, node_t b) {
	return a.score - b.score;
}

bool item_equal(item_t a, item_t b) {
	return point_equal(a.pt, b.pt) && a.dir == b.dir;
}

bool point_equal(point_t left, point_t right) {
	return left.x == right.x && left.y == right.y;
}