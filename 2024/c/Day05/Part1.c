/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 5 of AOC.
 * Vers: 1.0.0 12/05/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

typedef struct array{
	uint64_t *data;
	size_t max;
	size_t sz;
} array_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);
array_t init_array(void);
void append_array(array_t *array, uint64_t el);
uint64_t get_array(array_t array, size_t index);
bool isvalid(array_t page, array_t order[100]);

int main(int argc, char **argv) {
    FILE *file;
	string_t string = init_str();
	array_t order[100];
	int left;
	int right;
	array_t *pages;
	size_t page_max = 100;
	size_t page_sz = 0;
	char *tok;
	bool *valid_pages;
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

	for (size_t i = 0; i < 100; ++i) {
		order[i] = init_array();
	}

	while (!feof(file)) {
		read_line(file, &string);
		
		if (string.str[0] == '\0') {
			break;
		}

		sscanf(string.str, "%d|%d", &left, &right);

		append_array(order + left, right);
	}

	pages = malloc(sizeof *pages * page_max);
	for (size_t i = 0; i < page_max; ++i) {
		pages[i] = init_array();
	}

	while (!feof(file)) {
		read_line(file, &string);

		if (string.str[0] == '\0') {
			break;
		}

		tok = strtok(string.str, ",");
		while (tok != NULL) {
			append_array(pages + page_sz, atoi(tok));
			tok = strtok(NULL, ",");
		}

		if (++page_sz >= page_max) {
			page_max += 100;

			pages = realloc(pages, sizeof *pages * page_max);

			for (size_t i = page_max - 100; i < page_max; ++i) {
				pages[i] = init_array();
			}
		}
	}

	for (size_t i = 0; i < page_sz; ++i) {
		if (isvalid(pages[i], order)) {
			total += pages[i].data[pages[i].sz / 2];
		}
	}


	printf("%zu\n", total);

	free_str(&string);

    return EXIT_SUCCESS;
}

string_t init_str(void) {
	string_t str = {NULL, 0, 100};
	str.str = calloc(str.cap, sizeof *str.str);

	return str;
}

void free_str(string_t *str) {
	if (str == NULL) {
		return;
	}

	if (str->str != NULL) {
		free(str->str);
		str->str = NULL;
		str->cap = 0;
		str->len = 0;
	}
}

void read_line(FILE *file, string_t *str) {
	char c;
	str->len = 0;

	if (str->cap == 0) {
		str->cap = 100;
		str->str = calloc(str->cap, sizeof *str->str);
	}

	while ((c = fgetc(file)) != EOF && c != '\n') {
		str->str[str->len++] = c;

		if (str->len >= str->cap) {
			str->cap *= 2;
			str->str = realloc(str->str, sizeof *str->str * str->cap);
		}
	}

	str->str[str->len++] = '\0';
}

array_t init_array(void) {
	array_t array;

	array.max = 100;
	array.sz = 0;

	array.data = malloc(sizeof *array.data * array.max);

	return array;
}

void append_array(array_t *array, uint64_t el) {
	if (array == NULL) {
		return;
	}

	if (array->sz >= array->max) {
		array->max *= 2;
		array->data = realloc(array->data, sizeof *array->data * array->max);
	}

	array->data[array->sz++] = el;
}

uint64_t get_array(array_t array, size_t index) {
	if (index >= array.sz) {
		return 0;
	}

	return array.data[index];
}

bool isvalid(array_t page, array_t order[100]) {
	bool seen[100] = {false};

	for (size_t i = 0; i < page.sz; ++i) {
		array_t o = order[page.data[i]];
		for (size_t j = 0; j < o.sz; ++j) {
			if (seen[o.data[j]]) {
				return false;
			}
		}
		seen[page.data[i]] = true;
	}

	return true;
}
