/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 15 of AOC.
 * Vers: 1.0.0 12/15/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long hash(const char *str) {
	unsigned long long value = 0;

	while (*str) {
		value = 17 * (value + *str++);
	}

	return value % 256;
}

char *readLine(FILE *file) {
    char *line = NULL;
    size_t sz = 1000;
    size_t count = 0;
    char c;

    if (feof(file)) {
        return NULL;
    }

    line = malloc(sizeof(*line) * sz);

    while ((c = getc(file)) != '\n' && c != EOF) {
        line[count++] = c;

        if (count >= sz) {
            sz *= 2;
            line = realloc(line, sizeof(*line) * sz);
        }
    }

    line[count] = '\0';

    if (count == 0) {
        free(line);
        return NULL;
    }

    return line;
}

int main(int argc, char **argv) {
    FILE *file;
	char *line;
	char *tok;
	unsigned long long ans = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	line = readLine(file);

	tok = strtok(line, ",");

	while(tok != NULL){
		ans += hash(tok);
		tok = strtok(NULL, ",");
	}

	printf("%llu\n", ans);

    return EXIT_SUCCESS;
}
