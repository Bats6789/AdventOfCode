/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 1 of AOC.
 * Vers: 1.0.0 12/01/2023 CBW - Original code.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char buf[6], char c) {
    for (int i = 0; i < 4; ++i) {
        buf[i] = buf[i + 1];
    }
    buf[4] = c;
}

int getPotVal(char buf[6]) {
    if (strncmp(buf + 2, "one", 3) == 0) {
        return 1;
    } else if (strncmp(buf + 2, "two", 3) == 0) {
        return 2;
    } else if (strncmp(buf, "three", 5) == 0) {
        return 3;
    } else if (strncmp(buf + 1, "four", 4) == 0) {
        return 4;
    } else if (strncmp(buf + 1, "five", 4) == 0) {
        return 5;
    } else if (strncmp(buf + 2, "six", 3) == 0) {
        return 6;
    } else if (strncmp(buf, "seven", 5) == 0) {
        return 7;
    } else if (strncmp(buf, "eight", 5) == 0) {
        return 8;
    } else if (strncmp(buf + 1, "nine", 4) == 0) {
        return 9;
    } else {
        return -1;
    }
}

int main(int argc, char **argv) {
    FILE *file;
    char c;
    char buf[6] = {0};
    int first;
    int last;
    int total;
	int tmp = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    total = 0;
    first = -1;
    last = -1;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            total += first * 10 + last;
            first = -1;
            last = -1;
			buf[4] = '\0';
        } else if (isdigit(c)) {
            if (first == -1) first = c - '0';
            last = c - '0';
        } else {
			push(buf, c);

			tmp = getPotVal(buf);
			if( tmp != -1 ){
				if (first == -1) first = tmp;
				last = tmp;
			}
		}
    }

    printf("%d\n", total);

    return EXIT_SUCCESS;
}
