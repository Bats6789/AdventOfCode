/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 12 of AOC.
 * Vers: 1.0.0 12/12/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 131072 // 2^17

typedef unsigned long long ull;

ull memoize[SIZE];

int hash(int index, int coordIndex, int current) {
    return ((index & 0x7F) << 10) | ((coordIndex & 0x1F) << 5) | (current & 0x1F);
}

void clearMemoize(void) {
    for (size_t i = 0; i < SIZE; ++i) {
        memoize[i] = -1;
    }
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

void parseLine(const char *line, char **row, ull **coord, size_t *coordSz) {
    char *tmp = strchr(line, ' ');
    size_t count = 0;
    ull val = 0;

    *row = malloc(sizeof(**row) * (tmp - line + 1));
    strncpy(*row, line, (tmp - line));
    (*row)[tmp - line] = '\0';

    *coordSz = 10;
    *coord = malloc(sizeof(**coord) * *coordSz);

    for (char *c = tmp + 1; *c != '\0'; ++c) {
        if (*c == ',') {
            (*coord)[count++] = val;
            val = 0;

            if (count >= *coordSz) {
                *coordSz *= 2;
                *coord = realloc(*coord, sizeof(**coord) * *coordSz);
            }
        } else {
            val = val * 10 + *c - '0';
        }
    }

    (*coord)[count++] = val;

    if (count != *coordSz) {
        *coordSz = count;
        *coord = realloc(*coord, sizeof(**coord) * *coordSz);
    }
}

ull getScore(const char *row, size_t rowSz, const ull *coord, size_t coordSz,
             int index, int coordIndex, int current) {
    ull key = hash(index, coordIndex, current);
    ull ans = 0;
    char checkMap[2] = {'.', '#'};

    if (memoize[key] != -1) {
        return memoize[key];
    }

    // end of list
    if (index == rowSz) {
        if (coordIndex == coordSz && current == 0) {  // all coords successful
            return 1;
            // The last coord is being processed, but it is successful
        } else if (coordIndex == coordSz - 1 && coord[coordIndex] == current) {
            return 1;
        } else {
            return 0;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (row[index] == checkMap[i] || row[index] == '?') {
            if (checkMap[i] == '.' && current == 0) {
				ans += getScore(row, rowSz, coord, coordSz, index + 1, coordIndex, 0);
            } else if (checkMap[i] == '.' && current > 0 &&
                       coordIndex < coordSz && coord[coordIndex] == current) {
				ans += getScore(row, rowSz, coord, coordSz, index + 1, coordIndex + 1, 0);
            } else if (checkMap[i] == '#') {
				ans += getScore(row, rowSz, coord, coordSz, index + 1, coordIndex, current + 1);
            }
        }
    }

    memoize[key] = ans;
    return ans;
}

int main(int argc, char **argv) {
    FILE *file = NULL;
    char *line = NULL;
    char *row;
    ull *coord;
    ull total = 0;
    size_t coordSz = 0;
	ull score = 0;

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
        parseLine(line, &row, &coord, &coordSz);
        clearMemoize();
        score = getScore(row, strlen(row), coord, coordSz, 0, 0, 0);
		total += score;
        free(coord);
        free(row);
        free(line);
    }

    printf("%llu\n", total);

    return EXIT_SUCCESS;
}
