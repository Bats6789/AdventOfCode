/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 9 of AOC.
 * Vers: 1.0.0 12/09/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int processArray(const int *array, size_t sz) {
    bool quit = true;
	int diffArray[sz - 1];

    for (size_t i = 0; i < sz; ++i) {
        if (array[i] != 0) {
            quit = false;
        }
    }

    if (quit) {
        return 0;
    }

	for(size_t i = 0; i < sz - 1; ++i){
		diffArray[i] = array[i + 1] - array[i];
	}

    return array[0] - processArray(diffArray, sz - 1);
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

int *lineToArray(char *line, size_t *sz) {
    char *tok;
    int *array = NULL;
    size_t count = 0;

    *sz = 1000;

    array = malloc(sizeof(*array) * *sz);

    tok = strtok(line, " ");

    while (tok != NULL) {
        array[count++] = atoi(tok);

        if (count >= *sz) {
            *sz *= 2;
            array = realloc(array, sizeof(*array) * *sz);
        }

        tok = strtok(NULL, " ");
    }

    *sz = count;
    array = realloc(array, sizeof(*array) * *sz);

    return array;
}

int main(int argc, char **argv) {
    FILE *file;
    char *line;
    int total = 0;
    int *array;
    size_t sz = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while ((line = readLine(file)) != NULL) {
        array = lineToArray(line, &sz);

        total += processArray(array, sz);
        free(line);
    }

    printf("%d\n", total);

    return EXIT_SUCCESS;
}
