/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 8 of AOC.
 * Vers: 1.0.0 12/08/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The hashmap size is 26^3 = 17576
#define HASHMAP_SZ 17576

typedef struct {
    char left[4];
    char right[4];
} node_t;

typedef enum { l = 0, r = 1 } direction_t;

direction_t *lineToInput(const char *line, size_t sz) {
    direction_t *input = malloc(sizeof(*input) * sz);

    for (size_t i = 0; i < sz; ++i) {
        input[i] = line[i] == 'L' ? l : r;
    }

    return input;
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

unsigned int hash(char key[4]) {
    return 676 * (key[0] - 'A') + 26 * (key[1] - 'A') + (key[2] - 'A');
}

int main(int argc, char **argv) {
    FILE *file;
    char *line;
    direction_t *input;
    char key[4];
    char left[4];
    char right[4];
    unsigned int hashIndex = 0;
    unsigned long long stepCount = 0;
    size_t inputLen = 0;
    node_t hashmap[HASHMAP_SZ] = {0};

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
    inputLen = strlen(line);

    input = lineToInput(line, inputLen);
    free(line);

    fgetc(file);  // read blank line

    while ((line = readLine(file)) != NULL) {
        sscanf(line, "%3s = (%3s, %3s)", key, left, right);
        hashIndex = hash(key);
        strcpy(hashmap[hashIndex].left, left);
        strcpy(hashmap[hashIndex].right, right);
        free(line);
    }

    key[0] = 'A';
    key[1] = 'A';
    key[2] = 'A';

    while (strcmp(key, "ZZZ") != 0) {
        if (input[stepCount % inputLen] == l) {
            strcpy(key, hashmap[hash(key)].left);
        } else {
            strcpy(key, hashmap[hash(key)].right);
        }
        stepCount++;
    }

	printf("%llu\n", stepCount);

    return EXIT_SUCCESS;
}
