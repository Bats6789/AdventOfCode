/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 13 of AOC.
 * Vers: 1.0.0 12/13/2024 CBW - Original code.
 */
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

typedef struct point {
	int64_t x;
	int64_t y;
} point_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);
uint64_t get_score(point_t prize, point_t a, point_t b);

int main(int argc, char **argv) {
    FILE *file;
	string_t str = init_str();
	point_t a, b, prize;
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

	read_line(file, &str); // Read A
	while (str.len > 0) {
		sscanf(str.str, "Button A: X+%"SCNi64", Y+%"SCNi64, &a.x, &a.y);

		read_line(file, &str); // Read B
		sscanf(str.str, "Button B: X+%"SCNi64", Y+%"SCNi64, &b.x, &b.y);

		read_line(file, &str); // Read prize
		sscanf(str.str, "Prize: X=%"SCNi64", Y=%"SCNi64, &prize.x, &prize.y);

		total += get_score(prize, a, b);
		read_line(file, &str); // read blank
		read_line(file, &str); // Attempt to read A
	}

	free_str(&str);

	printf("%"PRIu64"\n", total);

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

uint64_t get_score(point_t prize, point_t a, point_t b) {
	int64_t det = a.x * b.y - b.x * a.y;
	int64_t a_n = prize.x * b.y - prize.y * b.x;
	int64_t b_n = prize.x * a.y - prize.y * a.x;

	if (det == 0 || a_n % det != 0 || b_n % det != 0) {
		return 0;
	}

	return 3 * a_n / det + b_n / det;
}
