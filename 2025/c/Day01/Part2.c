/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/01/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file;
	int number = 50;
	int num;
	char c;
	unsigned int count = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	while (fscanf(file, "%c%d\n", &c, &num) != EOF) {
		if (num >= 100) {
			count += num / 100;
			num %= 100;
		}

		if (c == 'L') {
			if (num > number) {
				if (number != 0) {
					count++;
				}
				number -= num;
				number += 100;
			} else {
				number -= num;
			}
		} else {
			number += num;
			if (number > 100) {
				count++;
			}
			number %= 100;
		}

		if (number == 0) {
			count++;
		}
	}

	printf("%d\n", count);

	fclose(file);

    return EXIT_SUCCESS;
}
