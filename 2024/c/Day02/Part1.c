/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/02/2024 CBW - Original code.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);
int count_spaces(const char *str);

int main(int argc, char **argv) {
    FILE *file;
	string_t string = init_str();
	uint64_t count = 0;
	int *list = NULL;
	int space_count = 0;
	int list_count = 0;
	char *tok;
	bool skip = false;
	int dir = 0;

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
		read_line(file, &string);

		if (string.len > 0) {
			space_count = count_spaces(string.str);

			list = malloc(sizeof *list * (space_count + 1));

			tok = strtok(string.str, " ");

			list_count = 0;
			while (tok != NULL) {
				list[list_count++] = strtol(tok, NULL, 10);
				tok = strtok(NULL, " ");
			}

			skip = false;
			dir = 0;
			for (size_t i = 0; i < list_count - 1; ++i) {
				if (dir == 0) {
					dir = list[i] - list[i + 1];
				}

				int dif = abs(list[i] - list[i + 1]);
				if (dif > 3 || dif < 1) {
					skip = true;
					break;
				}

				if (dir < 0 && list[i] > list[i + 1]) {
					skip = true;
					break;
				} else if (dir > 0 && list[i] < list[i + 1]) {
					skip = true;
					break;
				}
			}

			free(list);

			if (!skip) {
				count++;
			}
		}
	}

	free_str(&string);

	printf("%"PRIu64"\n", count);

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

int count_spaces(const char *str) {
	int count = 0;

	for (const char *c = str; *c != '\0'; ++c) {
		if (*c == ' ') {
			count++;
		}
	}

	return count;
}
