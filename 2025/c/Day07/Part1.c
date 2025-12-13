/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 7 of AOC.
 * Vers: 1.0.0 12/07/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

typedef struct set_t {
	int *items;
	size_t sz;
	size_t cap;
} set_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);

set_t init_set(void);
void add_id(set_t *set, int item);
bool in_set(set_t set, int item);
void copy_set(set_t *dest, set_t *src);

int main(int argc, char **argv) {
    FILE *file;
	set_t beams = init_set();
	set_t new_beams = init_set();
	string_t str = init_str();
	unsigned long long count = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	read_line(file, &str);
	for (int i = 0; i < str.len; ++i) {
		if (str.str[i] == 'S') {
			add_id(&beams, i);
		}
	}

	while (!feof(file)) {
		read_line(file, &str);

		if (str.len == 0) {
			continue;
		}

		new_beams.sz = 0;

		for (size_t i = 0; i < beams.sz; ++i) {
			if (0 <= beams.items[i] && beams.items[i] < str.len && str.str[beams.items[i]] == '^') {
				count += 1;
				add_id(&new_beams, beams.items[i] - 1);
				add_id(&new_beams, beams.items[i] + 1);
			} else {
				add_id(&new_beams, beams.items[i]);
			}
		}

		copy_set(&beams, &new_beams);
	}

	printf("%llu\n", count);

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

	str->str[str->len] = '\0';
}

set_t init_set(void) {
	set_t set = {NULL, 0, 100};

	set.items = malloc(sizeof(*set.items) * set.cap);

	return set;
}

void add_id(set_t *set, int item) {
	if (!in_set(*set, item)) {
		if (set->sz == set->cap) {
			set->cap *= 2;
			set->items = realloc(set->items, sizeof(*set->items) * set->cap);
		}

		set->items[set->sz++] = item;
	}
}

bool in_set(set_t set, int item) {
	for (size_t i = 0; i < set.sz; ++i) {
		if (set.items[i] == item) {
			return true;
		}
	}

	return false;
}

void copy_set(set_t *dest, set_t *src) {
	if (dest->cap < src->cap) {
		dest->cap = src->cap;

		dest->items = realloc(dest->items, sizeof(*dest->items) * dest->cap);
	}

	dest->sz = src->sz;

	memcpy(dest->items, src->items, sizeof(*dest->items) * dest->sz);
}
