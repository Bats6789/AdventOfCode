/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 18 of AOC.
 * Vers: 1.0.0 12/18/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} pt_t;

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
    int dist;
    long long int area;
    long long int boundaryCount = 0;
    long long int internalArea;
    char dir;
    char color[7];
    pt_t *points;
    size_t ptsSz = 100;
    ssize_t ptsCount = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    points = malloc(sizeof(*points) * ptsSz);
    points[ptsCount++] = (pt_t){0, 0};

    while ((line = readLine(file)) != NULL) {
        sscanf(line, "%c %d (#%6s)", &dir, &dist, color);

        boundaryCount += dist;
        points[ptsCount] = points[ptsCount - 1];

        switch (dir) {
            case 'U':
                points[ptsCount].y -= dist;
                break;
            case 'D':
                points[ptsCount].y += dist;
                break;
            case 'L':
                points[ptsCount].x -= dist;
                break;
            case 'R':
                points[ptsCount].x += dist;
                break;
        }

        if (++ptsCount >= ptsSz) {
            ptsSz *= 2;
            points = realloc(points, sizeof(*points) * ptsSz);
        }

        free(line);
    }

    area = 0;
    for (int i = 0; i < ptsCount; ++i) {
        area += points[i].y *
                (points[(i - 1) % ptsCount].x - points[(i + 1) % ptsCount].x);
    }

    area = llabs(area) / 2;

    internalArea = area - boundaryCount / 2 + 1;

    printf("%lld\n", internalArea + boundaryCount);

    return EXIT_SUCCESS;
}
