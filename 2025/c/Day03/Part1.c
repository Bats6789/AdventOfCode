/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 3 of AOC.
 * Vers: 1.0.0 12/03/2025 CBW - Original code.
 */
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
unsigned long long getMaxJolt(string_t str);

int main(int argc, char **argv) {
    FILE *file;
	string_t line = init_str();
	unsigned long long total = 0;

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
			total += getMaxJolt(line);
		}
	}

	free_str(&line);
	printf("%llu\n", total);

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

unsigned long long getMaxJolt(string_t line) {
	unsigned long long maxVal = 0;
	unsigned long long val = 0;

	if (line.len == 0) {
		return 0;
	}

	for (size_t i = 0; i < line.len - 1; ++i) {
		for (size_t j = i + 1; j < line.len; ++j) {
			val = (line.str[i] - '0') * 10 + (line.str[j] - '0');
			maxVal = val > maxVal ? val : maxVal;
		}
	}

	return maxVal;
}
