/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 2 of AOC.
 * Vers: 1.0.0 12/02/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


bool isInvalid(unsigned long long value) {
	size_t length = floor(log10(value)) + 1;
	unsigned long long tmp = 0;
	unsigned long long half_value = 0;

	for (size_t i = 0; i < length / 2; ++i) {
		tmp *= 10;
		tmp += value % 10;
		value /= 10;
	}

	for (size_t i = 0; i < length / 2; ++i) {
		half_value *= 10;
		half_value += tmp % 10;
		tmp /= 10;
	}

	return value == half_value;
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
