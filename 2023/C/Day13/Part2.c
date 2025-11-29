/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 13 of AOC.
 * Vers: 1.0.0 12/13/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *cells;
    size_t height;
    size_t width;
} grid_t;

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

grid_t fileToGrid(FILE *file) {
    grid_t grid = {0, 0, 0};
    char *line = NULL;
    size_t lineCount = 0;

    if (feof(file)) {
        return grid;
    }

    line = readLine(file);
    if (line == NULL) {
        return grid;
    }

    grid.width = strlen(line);
    grid.height = 10;
    grid.cells = malloc(sizeof(*grid.cells) * grid.width * grid.height);

    do {
        strncpy(grid.cells + lineCount++ * grid.width, line, grid.width);
        if (lineCount >= grid.height) {
            grid.height *= 2;
            grid.cells = realloc(
                grid.cells, sizeof(*grid.cells) * grid.width * grid.height);
        }
    } while ((line = readLine(file)) != NULL);

    grid.height = lineCount;
    grid.cells =
        realloc(grid.cells, sizeof(*grid.cells) * grid.width * grid.height);

    return grid;
}

void printGrid(grid_t grid) {
    for (size_t row = 0; row < grid.height; ++row) {
        for (size_t col = 0; col < grid.width; ++col) {
            putchar(grid.cells[row * grid.width + col]);
        }
        putchar('\n');
    }
}

int getRowDiff(const char *cells, size_t sz) {
    int difference = 0;
    for (size_t i = 0; i < sz / 2; ++i) {
        if (cells[i] != cells[sz - i - 1]) {
            difference++;
        }
    }

    return difference;
}

int getColDiff(const char *cells, size_t sz, size_t rowSz) {
    int difference = 0;
    for (size_t i = 0; i < sz / 2; ++i) {
        if (cells[rowSz * i] != cells[rowSz * (sz - i - 1)]) {
            difference++;
        }
    }
    return difference;
}

unsigned long long getMirror(grid_t grid) {
    bool isMirror = false;
    char *tmp;
    int difference = 0;
    unsigned long long rowCount = 999999;
    unsigned long long colCount = 999999;

    // get col set
    for (size_t i = 1; i < grid.width; ++i) {
        isMirror = true;
        difference = 0;
        for (size_t row = 0; row < grid.height && isMirror; ++row) {
            tmp = grid.cells + row * grid.width;
            if (i > grid.width / 2) {
                difference += getRowDiff(tmp + 1 + 2 * (i - grid.width / 2 - 1),
                                         2 * (grid.width - i));
            } else {
                difference += getRowDiff(tmp, 2 * i);
            }
        }

        if (difference == 1) {
            // printf("col: %d\n", i);
            colCount = i;
            break;
        }
    }

    // get row set
    for (size_t i = 1; i < grid.height; ++i) {
        isMirror = true;
        difference = 0;
        for (size_t col = 0; col < grid.width && isMirror; ++col) {
            tmp = grid.cells + col;
            if (i > grid.height / 2) {
                difference += getColDiff(
                    tmp + grid.width * (1 + 2 * (i - grid.height / 2 - 1)),
                    2 * (grid.height - i), grid.width);
            } else {
                difference += getColDiff(tmp, 2 * i, grid.width);
            }
        }

        if (difference == 1) {
            // printf("row: %d\n", i);
            rowCount = i;
            break;
        }
    }

    return colCount < rowCount ? colCount : 100 * rowCount;
}

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
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

    while (!feof(file) && (grid = fileToGrid(file)).cells != NULL) {
        ans += getMirror(grid);
		free(grid.cells);
    }

    printf("%llu\n", ans);

    return EXIT_SUCCESS;
}
