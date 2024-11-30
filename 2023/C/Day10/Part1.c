/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 10 of AOC.
 * Vers: 1.0.0 12/10/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int dist;
} point_t;

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
    char **grid;
    char *line;
    int **distMap;
    size_t rowSz = 0;
    size_t colSz = 0;
    size_t queueCount = 0;
    size_t rowCount = 0;
    point_t sLoc = {-1, -1};
    point_t queue[3];
    point_t pt;
    point_t newPt;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    rowSz = 100;
    grid = malloc(sizeof(*grid) * rowSz);

    while ((line = readLine(file)) != NULL) {
        grid[rowCount++] = line;

        // Find S
        if (sLoc.x == -1) {
            for (size_t i = 0; line[i] != '\0'; ++i) {
                if (line[i] == 'S') {
                    sLoc.x = i;
                    sLoc.y = rowCount - 1;
                    sLoc.dist = 0;
                    break;
                }
            }
        }

        // allocate more memory as needed
        if (rowCount >= rowSz) {
            rowSz *= 2;
            grid = realloc(grid, sizeof(*grid) * rowSz);
        }
    }

    rowSz = rowCount;
    grid = realloc(grid, sizeof(*grid) * rowSz);
    colSz = strlen(grid[0]);

    distMap = malloc(sizeof(*distMap) * rowSz);
    for (size_t i = 0; i < rowSz; ++i) {
        distMap[i] = malloc(sizeof(**distMap) * colSz);
        memset(distMap[i], -1, sizeof(**distMap) * colSz);
    }

    queue[queueCount++] = sLoc;
    while (queueCount > 0) {
        pt = queue[0];
		queueCount--;
		for (size_t i = 0; i < queueCount; ++i) {
			queue[i] = queue[i + 1];
		}

        if (distMap[pt.y][pt.x] != -1) {
            break;
        }

        distMap[pt.y][pt.x] = pt.dist;
        switch (grid[pt.y][pt.x]) {
            case 'S':
				char c = grid[pt.y - 1][pt.x];

				if (c == '|' || c == '7' || c == 'F') {
					newPt.y = pt.y - 1;
					newPt.x = pt.x;
					newPt.dist = pt.dist + 1;
					queue[queueCount++] = newPt;
				}

				c = grid[pt.y + 1][pt.x];
				if (c == '|' || c == 'J' || c == 'L') {
					newPt.y = pt.y + 1;
					newPt.x = pt.x;
					newPt.dist = pt.dist + 1;
					queue[queueCount++] = newPt;
				}

				c = grid[pt.y][pt.x - 1];
				if (c == '-' || c == 'L' || c == 'F') {
					newPt.y = pt.y;
					newPt.x = pt.x - 1;
					newPt.dist = pt.dist + 1;
					queue[queueCount++] = newPt;
				}

				c = grid[pt.y][pt.x + 1];
				if (c == '-' || c == 'J' || c == '7') {
					newPt.y = pt.y;
					newPt.x = pt.x + 1;
					newPt.dist = pt.dist + 1;
					queue[queueCount++] = newPt;
				}
                break;
            case '|':
                if (distMap[pt.y - 1][pt.x] == -1) {
                    newPt.y = pt.y - 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y + 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
                break;
            case 'F':
                if (distMap[pt.y + 1][pt.x] == -1) {
                    newPt.y = pt.y + 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y;
                    newPt.x = pt.x + 1;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
				break;
            case '7':
                if (distMap[pt.y + 1][pt.x] == -1) {
                    newPt.y = pt.y + 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y;
                    newPt.x = pt.x - 1;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
				break;
            case 'L':
                if (distMap[pt.y - 1][pt.x] == -1) {
                    newPt.y = pt.y - 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y;
                    newPt.x = pt.x + 1;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
				break;
            case '-':
                if (distMap[pt.y][pt.x + 1] == -1) {
                    newPt.y = pt.y;
                    newPt.x = pt.x + 1;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y;
                    newPt.x = pt.x - 1;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
				break;
            case 'J':
                if (distMap[pt.y][pt.x - 1] == -1) {
                    newPt.y = pt.y;
                    newPt.x = pt.x - 1;
                    newPt.dist = pt.dist + 1;
                } else {
                    newPt.y = pt.y - 1;
                    newPt.x = pt.x;
                    newPt.dist = pt.dist + 1;
                }
                queue[queueCount++] = newPt;
				break;
        }
    }

	printf("%d\n", distMap[pt.y][pt.x]);

    return EXIT_SUCCESS;
}
