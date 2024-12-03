/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 3 of AOC.
 * Vers: 1.0.0 12/03/2024 CBW - Original code.
 */
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

typedef enum state {
	beginning, first, second
} state_t;

int main(int argc, char **argv) {
    FILE *file;
	char *start;
	char c;
	size_t count = 0;
	char prev;
	int64_t first_val = 0;
	int64_t second_val = 0;
	int64_t total = 0;
	bool is_negative = false;
	bool first_char = false;
	state_t state = beginning;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	while ((c = fgetc(file)) != EOF) {
		switch (state) {
			case beginning:
				switch (c) {
					case 'm':
						count = 1;
						break;
					case 'u':
						if (count == 1) {
							count = 2;
						} else {
							count = 0;
						}
						break;
					case 'l':
						if (count == 2) {
							count = 3;
						} else {
							count = 0;
						}
						break;
					case '(':
						if (count == 3) {
							count = 0;
							state = first;
							first_val = 0;
							second_val = 0;
							is_negative = false;
							first_char = true;
						} else {
							count = 0;
						}
						break;
					default:
						count = 0;
				}
				break;
			case first:
				if (isdigit(c)) {
					first_val = first_val * 10 + (c - '0');
					first_char = false;
				} else if (c == '-') {
					if (prev == '(') {
						is_negative = true;
					} else {
						state = beginning;
					}
				} else if (c == ',') {
					if (is_negative) {
						first_val = -first_val;
					}

					state = first_char ? beginning : second;
					first_char = true;
				} else {
					state = beginning;
					if (c == 'm') {
						count = 1;
					}
				}
				break;
			case second:
				if (isdigit(c)) {
					second_val = second_val * 10 + (c - '0');
					first_char = false;
				} else if (c == '-') {
					if (prev == ',') {
						is_negative = true;
					} else {
						state = beginning;
					}
				} else if (c == ')') {
					state = beginning;
					if (is_negative) {
						second_val = -second_val;
					}

					if (!first_char) {
						total += first_val * second_val;
					}
				} else {
					state = beginning;
					if (c == 'm') {
						count = 1;
					}
				}
				break;
        }
		prev = c;
	}

	printf("%"PRIi64"\n", total);

    return EXIT_SUCCESS;
}
