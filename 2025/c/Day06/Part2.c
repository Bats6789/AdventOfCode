/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 6 of AOC.
 * Vers: 1.0.0 12/06/2025 CBW - Original code.
 */
#include <assert.h>
#include <stdbool.h>
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

int main(int argc, char **argv) {
    FILE *file;
	string_t lines[5];
	string_t tmp_string;
	size_t line_count = 0;
	long long values[4] = {0};
	size_t value_count = 0;
	long long total = 0;
	long long tmp = 0;
	char op = '+';
	bool is_blank_column = false;
	size_t max_line_length = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	for (size_t i = 0; i < 5; ++i) {
		lines[i] = init_str();
	}

	while (!feof(file)) {
		tmp_string = (string_t){NULL, 0, 0};
		read_line(file, &tmp_string);

		if (tmp_string.len != 0) {
			lines[line_count++] = tmp_string;
		}
	}

	fclose(file);

	for (size_t i = 0; i < line_count; ++i) {
		max_line_length = max_line_length > lines[i].len ? max_line_length : lines[i].len;
	}

	for (size_t i = 0; i < max_line_length; ++i) {
		if (i < lines[line_count - 1].len && lines[line_count - 1].str[i] != ' ') {
			op = lines[line_count - 1].str[i];
		}

		is_blank_column = true;
		for (size_t j = 0; j < line_count; ++j) {
			if (i < lines[j].len && lines[j].str[i] != ' ') {
				is_blank_column = false;
				break;
			}
		}

		if (is_blank_column) {
			tmp = op == '+' ? 0 : 1;
			for (size_t j = 0; j < value_count; ++j) {
				if (op == '+') {
					tmp += values[j];
				} else {
					tmp *= values[j];
				}
			}

			total += tmp;

			for (size_t j = 0; j < value_count; ++j) {
				values[j] = 0;
			}
			value_count = 0;
		} else {
			for (size_t j = 0; j < line_count - 1; ++j) {
				if (i < lines[j].len && lines[j].str[i] != ' ') {
					values[value_count] *= 10;
					values[value_count] += lines[j].str[i] - '0';
				} 
			}
			value_count++;
		}
	}

	tmp = op == '+' ? 0 : 1;
	for (size_t j = 0; j < value_count; ++j) {
		if (op == '+') {
			tmp += values[j];
		} else {
			tmp *= values[j];
		}
	}

	total += tmp;

	for (size_t j = 0; j < value_count; ++j) {
		values[j] = 0;
	}
	value_count = 0;

	printf("%lld\n", total);

	for (size_t i = 0; i < line_count; ++i) {
		free_str(lines + i);
	}

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
