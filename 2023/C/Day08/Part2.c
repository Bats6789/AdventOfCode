/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 8 of AOC.
 * Vers: 1.0.0 12/08/2023 CBW - Original code.
 */
#include <stdbool.h>
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
typedef unsigned long long ull;

ull gcd(ull a, ull b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ull lcm(ull *array, size_t sz) {
    ull a;
    ull b;

    if (array == NULL) {
        return 0;
    }
    a = *array;

    if (sz == 1) {
        return a;
    }
    b = sz <= 2 ? *(array + 1) : lcm(array + 1, sz - 1);

    return (a / gcd(a, b)) * b;
}

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
    char startKeys[6][4];
    char searchKeys[6][4];
    char left[4];
    char right[4];
    unsigned int hashIndex = 0;
    ull stepCount = 0;
    ull cycleLengths[6] = {0, 0, 0, 0, 0, 0};
    size_t inputLen = 0;
    size_t startKeyCount = 0;
    node_t hashmap[HASHMAP_SZ] = {0};
    bool searching[6] = {true, true, true, true, true, true};
    bool done = false;

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
        if (key[2] == 'A') {
            strcpy(startKeys[startKeyCount], key);
            strcpy(searchKeys[startKeyCount], key);
            startKeyCount++;
        }
        free(line);
    }

    while (!done) {
        for (size_t i = 0; i < startKeyCount; ++i) {
            if (searching[i]) {
                if (input[stepCount % inputLen] == l) {
                    strcpy(searchKeys[i], hashmap[hash(searchKeys[i])].left);
                } else {
                    strcpy(searchKeys[i], hashmap[hash(searchKeys[i])].right);
                }

                if (searching[i] && strcmp(searchKeys[i], startKeys[i]) == 0) {
                    searching[i] = false;
                    cycleLengths[i] = stepCount - cycleLengths[i];
                } else if (startKeys[i][2] == 'A' && searchKeys[i][2] == 'Z') {
                    strcpy(startKeys[i], searchKeys[i]);
                    cycleLengths[i] = stepCount;
                }
            }
        }
        stepCount++;
        done = true;
        for (size_t i = 0; i < startKeyCount; ++i) {
            if (searching[i]) {
                done = false;
            }
        }
    }

    printf("%llu\n", lcm(cycleLengths, startKeyCount));

    return EXIT_SUCCESS;
}
