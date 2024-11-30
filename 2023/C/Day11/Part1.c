/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 11 of AOC.
 * Vers: 1.0.0 12/11/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCALE 1

typedef struct {
    int x;
    int y;
} point_t;

static inline int distance(point_t p1, point_t p2){
	return abs(p2.x - p1.x) + abs(p2.y - p1.y);
}

bool isEmptyCol(char **map, size_t sz, int j) {
    for (size_t i = 0; i < sz; ++i) {
		if (map[i][j] == '#') {
			return false;
		}
    }

    return true;
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
    FILE *file = NULL;
    point_t *planets = NULL;
    char **map = NULL;
    char *line = NULL;
    size_t planetsSz = 100;
    size_t planetsCount = 0;
    size_t mapSz = 100;
    size_t mapCount = 0;
    size_t mapLen = 0;
    size_t row = 0;
    size_t col = 0;
    size_t rowShift = 0;
    size_t *colShift = NULL;
    size_t colShiftVal = 0;
    char c = '\0';
	unsigned long long total = 0;
    bool seenPlanet = false;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    map = malloc(sizeof(*map) * mapSz);
    while ((line = readLine(file)) != NULL) {
        map[mapCount++] = line;
        if (mapCount >= mapSz) {
            mapSz *= 2;
            map = realloc(map, sizeof(*map) * mapSz);
        }
    }
    mapSz = mapCount;
    map = realloc(map, sizeof(*map) * mapSz);
    mapLen = strlen(map[0]);
    colShift = calloc(mapLen, sizeof(*colShift));

	planets = malloc(sizeof(*planets) * planetsSz);
    for (size_t i = 0; i < mapSz; ++i) {
        seenPlanet = false;

        for (size_t j = 0; j < mapLen; ++j) {
            if (i == 0) {
                if (isEmptyCol(map, mapSz, j)) {
                    colShiftVal++;
                }
                colShift[j] = colShiftVal;
            }

			if (map[i][j] == '#') {
				planets[planetsCount].x = j + colShift[j] * SCALE;
				planets[planetsCount++].y = i + rowShift * SCALE;
				seenPlanet = true;

				if (planetsCount >= planetsSz) {
					planetsSz *= 2;
					planets = realloc(planets, sizeof(*planets) * planetsSz);
				}
			}
        }

        if (!seenPlanet) {
            rowShift += 1;
        }
    }

	planetsSz = planetsCount;
	planets = realloc(planets, sizeof(*planets) * planetsSz);

	for (size_t i = 0; i < planetsSz - 1; ++i) {
		for (size_t j = i; j < planetsSz; ++j) {
			total += distance(planets[i], planets[j]);
		}
	}

	printf("%llu\n", total);

    return EXIT_SUCCESS;
}
