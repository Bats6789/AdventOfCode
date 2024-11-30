/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 3 of AOC.
 * Vers: 1.0.0 12/03/2023 CBW - Original code.
 */
#include <ctype.h>
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

long long int getNum(grid_t grid, size_t row, size_t col) {
    size_t start = col;
    size_t stop = col;
    long long int num = 0;

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
    long long int total = 0;
    int top;
    int bottom;
    int points[2][2];
    int pointCount = 0;

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
            top = 0;
            bottom = 0;
            pointCount = 0;
            if (grid.grid[i * grid.width + j] == '*') {
                char tmpc;
                // top
                if (i > 0) {
                    tmpc = grid.grid[(i - 1) * grid.width + j];
                    if (isdigit(tmpc)) {
                        top = 1;
                        points[pointCount][0] = i - 1;
                        points[pointCount++][1] = j;
                    }
                }
                // bottom
                if (i < grid.height - 1) {
                    tmpc = grid.grid[(i + 1) * grid.width + j];
                    if (isdigit(tmpc)) {
                        bottom = 1;
                        points[pointCount][0] = i + 1;
                        points[pointCount++][1] = j;
                    }
                }
                // left
                if (j > 0) {
                    tmpc = grid.grid[i * grid.width + (j - 1)];
                    if (isdigit(tmpc)) {
                        points[pointCount][0] = i;
                        points[pointCount++][1] = j - 1;
                    }
                }
                // right
                if (j < grid.width - 1) {
                    tmpc = grid.grid[i * grid.width + (j + 1)];
                    if (isdigit(tmpc)) {
                        points[pointCount][0] = i;
                        points[pointCount++][1] = j + 1;
                    }
                }
                // topleft
                if (i > 0 && j > 0) {
                    tmpc = grid.grid[(i - 1) * grid.width + (j - 1)];
                    if (isdigit(tmpc) && !top) {
                        points[pointCount][0] = i - 1;
                        points[pointCount++][1] = j - 1;
                    }
                }
                // topright
                if (i > 0 && j < grid.width - 1) {
                    tmpc = grid.grid[(i - 1) * grid.width + (j + 1)];
                    if (isdigit(tmpc) && !top) {
                        points[pointCount][0] = i - 1;
                        points[pointCount++][1] = j + 1;
                    }
                }
                // bottomleft
                if (i < grid.height - 1 && j > 0) {
                    tmpc = grid.grid[(i + 1) * grid.width + (j - 1)];
                    if (isdigit(tmpc) && !bottom) {
                        points[pointCount][0] = i + 1;
                        points[pointCount++][1] = j - 1;
                    }
                }
                // bottomright
                if (i < grid.height - 1 && j < grid.width - 1) {
                    tmpc = grid.grid[(i + 1) * grid.width + (j + 1)];
                    if (isdigit(tmpc) && !bottom) {
                        points[pointCount][0] = i + 1;
                        points[pointCount++][1] = j + 1;
                    }
                }

                if (pointCount == 2) {
                    long long int num1 =
                        getNum(grid, points[0][0], points[0][1]);
                    long long int num2 =
                        getNum(grid, points[1][0], points[1][1]);
                    total += num1 * num2;
                }
            }
        }
    }

    printf("%lld\n", total);
    return EXIT_SUCCESS;
}
