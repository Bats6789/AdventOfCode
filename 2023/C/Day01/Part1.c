/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 1 of AOC.
 * Vers: 1.0.0 12/01/2023 CBW - Original code.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file;
    char c;
    int first;
    int last;
    int total;

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
        } else if (isdigit(c)) {
            if (first == -1) first = c - '0';
            last = c - '0';
        }
    }

    printf("%d\n", total);

    return EXIT_SUCCESS;
}
