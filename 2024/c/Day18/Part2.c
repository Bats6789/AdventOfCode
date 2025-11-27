/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 18 of AOC.
 * Vers: 1.0.0 12/18/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t width = 71;
size_t height = 71;

typedef struct point {
	int x;
	int y;
} point_t;

typedef struct node {
	point_t pt;
	size_t count;
} node_t;

typedef struct heapq {
	node_t *data;
	size_t sz;
	size_t max;
} heapq_t;

heapq_t init_queue(void);
size_t parent(size_t i);
size_t left_child(size_t i);
size_t right_child(size_t i);
void shift_down(heapq_t *q, size_t i);
void shift_up(heapq_t *q, size_t i);
node_t pop_queue(heapq_t *q);
void push_queue(heapq_t *q, node_t el);
int cmp_node(node_t a, node_t b);
bool point_equal(point_t left, point_t right);
bool in_queue(heapq_t q, node_t node);
ssize_t get_path_count(char *grid);

int main(int argc, char **argv) {
    FILE *file;
	char *grid;
	point_t pt;
	size_t count = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

	if (argc == 4) {
		width = atoi(argv[2]);
		height = atoi(argv[3]);
	}

	grid = malloc(sizeof *grid * width * height);
	memset(grid, '.', width * height);

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	while (fscanf(file, "%d,%d\n", &pt.x, &pt.y) != EOF) {
		grid[pt.y * width + pt.x] = '#';
		if (get_path_count(grid) == -1) {
			break;
		}
	}

	fclose(file);

	printf("%d,%d\n", pt.x, pt.y);

	free(grid);

    return EXIT_SUCCESS;
}

inline bool point_equal(point_t left, point_t right) {
	return left.x == right.x && left.y == right.y;
}

ssize_t get_path_count(char *grid) {
	point_t start = {0, 0};
	point_t stop = {width - 1, height - 1};
	point_t loc = start;
	node_t node;
	heapq_t pq = init_queue();
	size_t count = 0;
	bool *visited = NULL;

	node.pt = start;
	node.count = count;

	push_queue(&pq, node);

	visited = malloc(sizeof *visited * width * height);
	for (size_t i = 0; i < width * height; ++i) {
		visited[i] = false;
	}

	while (!point_equal(loc, stop) && pq.sz != 0) {
		node = pop_queue(&pq);
		loc = node.pt;
		count = node.count;

		if (point_equal(loc, stop)) {
			break;
		}

		visited[loc.y * width + loc.x] = true;

		node.pt.x -= 1;
		node.count += 1;
		if (loc.x > 0 && !in_queue(pq, node) &&
			!visited[node.pt.y * width + node.pt.x] &&
			grid[node.pt.y * width + node.pt.x] == '.') {
			push_queue(&pq, node);
		}
		node.pt.x = loc.x;
		node.pt.x += 1;
		if (loc.x < width - 1 && !in_queue(pq, node) &&
			!visited[node.pt.y * width + node.pt.x] &&
			grid[node.pt.y * width + node.pt.x] == '.') {
			push_queue(&pq, node);
		}
		node.pt.x = loc.x;
		node.pt.y += 1;
		if (loc.y < height - 1 && !in_queue(pq, node) &&
			!visited[node.pt.y * width + node.pt.x] &&
			grid[node.pt.y * width + node.pt.x] == '.') {
			push_queue(&pq, node);
		}
		node.pt.y = loc.y;
		node.pt.y -= 1;
		if (loc.y > 0 && !in_queue(pq, node) &&
			!visited[node.pt.y * width + node.pt.x] &&
			grid[node.pt.y * width + node.pt.x] == '.') {
			push_queue(&pq, node);
		}
		node.pt.y = loc.y;
	}

	free(pq.data);

	return point_equal(loc, stop) ? count : -1;
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
		return (node_t){{-1, -1}, 0};
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

bool in_queue(heapq_t q, node_t node) {
	for (size_t i = 0; i < q.sz; ++i) {
		if (point_equal(node.pt, q.data[i].pt)) {
			return true;
		}
	}
	return false;
}

int cmp_node(node_t a, node_t b) {
	return a.count - b.count;
}
