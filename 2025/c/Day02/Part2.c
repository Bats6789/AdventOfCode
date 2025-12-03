/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 2 of AOC.
 * Vers: 1.0.0 12/02/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool isInvalid(unsigned long long value) {
	size_t length = floor(log10(value)) + 1;
	char *str = NULL;
	bool match = false;

	str = malloc(sizeof(*str) * (length + 1));
	snprintf(str, length + 1, "%llu", value);

	for (size_t i = 1; i <= length / 2; ++i) {
		if (length % i != 0) {
			continue;
		}
		match = true;

		for (size_t j = 1; j < length / i; ++j) {
			if (strncmp(str + i * (j - 1), str + i * j, i) != 0) {
				match = false;
				break;
			}
		}

		if (match) {
			return true;
		}
	}


	free(str);

	return false;
}

int main(int argc, char **argv) {
    FILE *file;
	unsigned long long start;
	unsigned long long stop;
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

	while (fscanf(file, "%llu-%llu,", &start, &stop) != EOF) {
		for (unsigned long long i = start; i <= stop; ++i) {
			if (isInvalid(i)) {
				total += i;
			}
		}
	}

	printf("%llu\n", total);

    return EXIT_SUCCESS;
}
