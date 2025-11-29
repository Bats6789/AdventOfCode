/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/01/2024 CBW - Original code.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct array {
	uint64_t *data;
	size_t max;
	size_t sz;
} array_t;

array_t init(void);
void append(array_t *array, uint64_t el);
uint64_t get(array_t array, size_t index);
void sort(array_t *array);
int cmp(const void *a, const void *b);
size_t count_el(array_t array, uint64_t el);

int main(int argc, char **argv) {
    FILE *file;
	array_t left = {NULL, 0, 0};
	array_t right = {NULL, 0, 0};
	uint64_t l;
	uint64_t r;
	uint64_t total = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	left = init();
	right = init();

	while (fscanf(file, "%"SCNu64" %"SCNu64"\n", &l, &r) != EOF) {
		append(&left, l);
		append(&right, r);
	}

	for (size_t i = 0; i < left.sz; ++i) {
		total += get(left, i) * count_el(right, get(left, i));
	}

	printf("%"PRIu64"\n", total);

    return EXIT_SUCCESS;
}

array_t init(void) {
	array_t array;

	array.max = 100;
	array.sz = 0;

	array.data = malloc(sizeof *array.data * array.max);

	return array;
}

void append(array_t *array, uint64_t el) {
	if (array == NULL) {
		return;
	}

	if (array->sz >= array->max) {
		array->max *= 2;
		array->data = realloc(array->data, sizeof *array->data * array->max);
	}

	array->data[array->sz++] = el;
}

uint64_t get(array_t array, size_t index) {
	if (index >= array.sz) {
		return 0;
	}

	return array.data[index];
}

void sort(array_t *array) {
	qsort(array->data, array->sz, sizeof *array->data, cmp);
}

int cmp(const void *a, const void *b) {
	uint64_t left = *(uint64_t *)a;
	uint64_t right = *(uint64_t *)b;

	return left - right;
}

size_t count_el(array_t array, uint64_t el) {
	size_t count = 0;

	for (size_t i = 0; i < array.sz; ++i ){
		if (el == array.data[i]) {
			count++;
		}
	}

	return count;
}
