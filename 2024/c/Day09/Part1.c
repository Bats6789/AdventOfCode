/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 9 of AOC.
 * Vers: 1.0.0 12/09/2024 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct block {
	int id;
	bool free;
	size_t rep;
} block_t;

typedef struct array {
    block_t *data;
    size_t max;
    size_t sz;
} array_t;

array_t init_array(void);
void append_array(array_t *array, block_t el);
void insert_array(array_t *array, block_t el, size_t i);
block_t get_array(array_t array, size_t index);

int main(int argc, char **argv) {
    FILE *file;
	array_t data = init_array();
	char c;
	block_t block = {0, false, 0};
	bool quit = false;
	size_t scale = 0;
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

	// build blocks
	while ((c = fgetc(file)) != EOF && c != '\n') {
		c -= '0';

		block.rep = c;
		append_array(&data, block);

		block.id = block.free ? block.id : block.id + 1;
		block.free = !block.free;
	}

	// shift blocks
	for (size_t i = 0; i < data.sz && !quit; ++i) {
		if (data.data[i].free) {
			for (ssize_t j = data.sz - 1; j >= 0; --j) {
				if (j <= i) {
					quit = true;
					break;
				}

				if (!data.data[j].free && data.data[j].rep > 0) {
					if (data.data[j].rep >= data.data[i].rep) {
						data.data[i].free = false;
						data.data[i].id = data.data[j].id;
						data.data[j].rep -= data.data[i].rep;
						break;
					} else {
						insert_array(&data, data.data[j], i);
						i += 1;
						j += 1;
						data.data[i].rep -= data.data[j].rep;
						data.data[j].rep = 0;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < data.sz; ++i) {
		if (data.data[i].free) {
			break;
		}

		for (size_t j = 0; j < data.data[i].rep; ++j) {
			total += data.data[i].id * scale++;
		}
	}

	printf("%zu\n", total);

	free(data.data);

    return EXIT_SUCCESS;
}

array_t init_array(void) {
    array_t array;

    array.max = 100;
    array.sz = 0;

    array.data = malloc(sizeof *array.data * array.max);

    return array;
}

void append_array(array_t *array, block_t el) {
    if (array == NULL) {
        return;
    }

    if (array->sz >= array->max) {
        array->max *= 2;
        array->data = realloc(array->data, sizeof *array->data * array->max);
    }

    array->data[array->sz++] = el;
}

void insert_array(array_t *array, block_t el, size_t index) {
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

block_t get_array(array_t array, size_t index) {
    if (index >= array.sz) {
        return (block_t){-1, false, 0};
    }

    return array.data[index];
}
