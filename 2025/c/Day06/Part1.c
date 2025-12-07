/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 6 of AOC.
 * Vers: 1.0.0 12/06/2025 CBW - Original code.
 */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct string {
    char *str;
    size_t len;
    size_t cap;
} string_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);
long long *parse_values(string_t str, size_t *sz);
char *parse_ops(string_t str, size_t *sz);

int main(int argc, char **argv) {
    FILE *file;
	string_t line = init_str();
	long long *values[4] = {NULL, NULL, NULL, NULL};
	size_t value_count = 0;
	size_t value_szs[4];
	char *ops;
	size_t op_sz;
	long long total = 0;
	long long tmp = 0;

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

		if (line.len != 0) {
			if (isdigit(line.str[0])) {
				values[value_count] = parse_values(line, value_szs + value_count);
				value_count += 1;
			} else {
				ops = parse_ops(line, &op_sz);
			}
		}
	}

	fclose(file);

	for (size_t i = 0; i < op_sz; ++i ) {
		tmp = ops[i] == '+' ? 0 : 1;
		for (size_t j = 0; j < value_count; ++j) {
			if (ops[i] == '+') {
				tmp += values[j][i];
			} else {
				tmp *= values[j][i];
			}
		}
		total += tmp;
	}

	printf("%lld\n", total);

	free_str(&line);
	for (size_t i = 0; i < value_count; ++i) {
		free(values[i]);
	}
	free(ops);

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

long long *parse_values(string_t str, size_t *sz) {
	size_t size = 0;
	size_t cap = 100;
	long long *values = NULL;
	size_t i = 0;
	int value;
	char *pos = str.str;
	char *end_pos = NULL;

	values = malloc(sizeof(*values) * cap);
	if (values == NULL) {
		return NULL;
	}

	while (str.str[i] != '\0') {
		while (*pos == ' ') {
			pos += 1;
		}

		if (*pos == '\0') {
			break;
		}

		errno = 0;
		value = strtoll(pos, &end_pos, 10);

		if (errno == ERANGE) {
			continue;
		}

		if (pos == end_pos) {
			break;
		}

		pos = end_pos;

		values[size++] = value;

		if (size >= cap) {
			cap *= 2;

			values = realloc(values, sizeof(*values) * cap);

			if (values == NULL) {
				return NULL;
			}
		}
	}

	values = realloc(values, sizeof(*values) * size);

	if (sz != NULL) {
		*sz = size;
	}

	return values;
}

char *parse_ops(string_t str, size_t *sz) {
	size_t size = 0;
	size_t cap = 100;
	char *ops = NULL;

	ops = malloc(sizeof(*ops) * cap);
	if (ops == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < str.len; ++i) {
		if (str.str[i] != ' ') {
			ops[size++] = str.str[i];
		}

		if (size >= cap) {
			cap *= 2;

			ops = realloc(ops, sizeof(*ops) * cap);

			if (ops == NULL) {
				return NULL;
			}
		}
	}

	ops = realloc(ops, sizeof(*ops) * size);

	if (sz != NULL) {
		*sz = size;
	}

	return ops;
}
