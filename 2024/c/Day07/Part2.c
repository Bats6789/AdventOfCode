/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 7 of AOC.
 * Vers: 1.0.0 12/07/2024 CBW - Original code.
 */
#include <inttypes.h>
#include <math.h>
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

typedef struct array {
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
void clear_array(array_t *array);
bool passing(uint64_t test, array_t values);

int main(int argc, char **argv) {
    FILE *file;
    uint64_t test = 0;
    array_t values = init_array();
    string_t line = init_str();
    char *tok;
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

    while (!feof(file)) {
        read_line(file, &line);

        if (line.len == 0) {
            continue;
        }

        test = strtoull(line.str, &tok, 10);

        if (test == 0 && line.str == tok) {
            perror("Parsing");
            exit(EXIT_FAILURE);
        }

        tok += 2;  // move past the seperator ": ".

        tok = strtok(tok, " ");
        while (tok != NULL) {
            append_array(&values, strtoull(tok, NULL, 10));
            tok = strtok(NULL, " ");
        }

        if (passing(test, values)) {
            total += test;
        }

        clear_array(&values);
    }

    free_str(&line);
    free(values.data);

    printf("%" PRIu64 "\n", total);

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

void clear_array(array_t *array) {
    if (array != NULL) {
        array->sz = 0;
    }
}

bool passing(uint64_t test, array_t values) {
    array_t new_array;
	uint64_t tmp;
	uint64_t concat_values;

    if (values.sz == 1) {
        return test == get_array(values, 0);
    }

    new_array = init_array();

    append_array(&new_array, get_array(values, 0) + get_array(values, 1));

    for (size_t i = 2; i < values.sz; ++i) {
        append_array(&new_array, values.data[i]);
    }

    if (passing(test, new_array)) {
        free(new_array.data);
        return true;
    }

    clear_array(&new_array);

    append_array(&new_array, get_array(values, 0) * get_array(values, 1));

    for (size_t i = 2; i < values.sz; ++i) {
        append_array(&new_array, values.data[i]);
    }

    if (passing(test, new_array)) {
        free(new_array.data);
        return true;
    }

	clear_array(&new_array);

	concat_values = get_array(values, 0);
	tmp = get_array(values, 1);
	
	concat_values = concat_values * pow(10, floor(log10(tmp)) + 1) + tmp;

    append_array(&new_array, concat_values);

    for (size_t i = 2; i < values.sz; ++i) {
        append_array(&new_array, values.data[i]);
    }

    if (passing(test, new_array)) {
        free(new_array.data);
        return true;
    }

    free(new_array.data);

    return false;
}
