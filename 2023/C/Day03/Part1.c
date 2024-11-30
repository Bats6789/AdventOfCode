/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 3 of AOC.
 * Vers: 1.0.0 12/03/2023 CBW - Original code.
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *grid;
    size_t height;
    size_t width;
} grid_t;

grid_t fileToGrid(FILE *file) {
    grid_t grid = {0, 0, 0};
    size_t currentSz = 0;
    size_t maxSize = 10000;
    char c;
    char lastc;

    grid.grid = malloc(sizeof(*grid.grid) * maxSize);

    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            grid.grid[currentSz++] = c;
        } else {
            grid.height++;
            if (grid.width == 0) {
                grid.width = currentSz;
            }
        }
        if (currentSz >= maxSize) {
            maxSize *= 2;
            grid.grid = realloc(grid.grid, sizeof(*grid.grid) * maxSize);
        }
        lastc = c;
    }
    if (lastc != '\n') {
        grid.height++;
    }

    grid.grid = realloc(grid.grid, sizeof(*grid.grid) * currentSz);
    return grid;
}

int getNum(grid_t grid, size_t row, size_t col) {
    size_t start = col;
    size_t stop = col;
    int num = 0;

    while (start > 0 && isdigit(grid.grid[row * grid.width + start])) {
        start--;
    }
    if (!isdigit(grid.grid[row * grid.width + start])) {
        start++;
    }
    while (stop < grid.width && isdigit(grid.grid[row * grid.width + stop])) {
        stop++;
    }

    for (int i = start; i < stop; ++i) {
        num = num * 10 + (grid.grid[row * grid.width + i] - '0');
    }

    return num;
}

int main(int argc, char **argv) {
    FILE *file;
    grid_t grid;
    int total = 0;
    int skip = 0;
    bool isgood = true;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    grid = fileToGrid(file);

    for (size_t i = 0; i < grid.height; ++i) {
        for (size_t j = 0; j < grid.width; ++j) {
            isgood = false;
            if (isdigit(grid.grid[i * grid.width + j]) && skip == 0) {
                char tmpc;
                // top
                if (i > 0) {
                    tmpc = grid.grid[(i - 1) * grid.width + j];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // bottom
                if (i < grid.height - 1) {
                    tmpc = grid.grid[(i + 1) * grid.width + j];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // left
                if (j > 0) {
                    tmpc = grid.grid[i * grid.width + (j - 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // right
                if (j < grid.width - 1) {
                    tmpc = grid.grid[i * grid.width + (j + 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // topleft
                if (i > 0 && j > 0) {
                    tmpc = grid.grid[(i - 1) * grid.width + (j - 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // topright
                if (i > 0 && j < grid.width - 1) {
                    tmpc = grid.grid[(i - 1) * grid.width + (j + 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // bottomleft
                if (i < grid.height - 1 && j > 0) {
                    tmpc = grid.grid[(i + 1) * grid.width + (j - 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }
                // bottomright
                if (i < grid.height - 1 && j < grid.width - 1) {
                    tmpc = grid.grid[(i + 1) * grid.width + (j + 1)];
                    if (tmpc != '.' && !isdigit(tmpc)) {
                        isgood = true;
                    }
                }

                if (isgood) {
                    total += getNum(grid, i, j);
                    size_t tmp;
                    for (tmp = j; tmp < grid.width &&
                                  isdigit(grid.grid[i * grid.width + tmp]);
                         ++tmp) {
                    }
                    skip = tmp - j;
                }
            } else if (skip > 0) {
                skip--;
            }
        }
    }

    printf("%d\n", total);
    return EXIT_SUCCESS;
}
