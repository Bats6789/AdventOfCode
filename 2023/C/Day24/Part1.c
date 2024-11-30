/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 24 of AOC.
 * Vers: 1.0.0 12/24/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 300

#define MIN_VAL 200000000000000
#define MAX_VAL 400000000000000

typedef struct {
    long long int x;
    long long int y;
    long long int z;
    long long int vx;
    long long int vy;
    long long int vz;
    double a;
    double b;
    double c;
} hailstone_t;

hailstone_t strToHail(const char *str) {
    hailstone_t hailstone = {0, 0, 0, 0, 0, 0};

    sscanf(str, "%lld, %lld, %lld @ %lld, %lld, %lld", &hailstone.x,
           &hailstone.y, &hailstone.z, &hailstone.vx, &hailstone.vy,
           &hailstone.vz);

    hailstone.a = hailstone.vy;
    hailstone.b = -hailstone.vx;
    hailstone.c = hailstone.vy * hailstone.x - hailstone.vx * hailstone.y;

    return hailstone;
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

void printHail(hailstone_t hailstone) {
    printf("%lld, %lld, %lld, @ %lld, %lld, %lld\n", hailstone.x, hailstone.y,
           hailstone.z, hailstone.vx, hailstone.vy, hailstone.vz);
}

int main(int argc, char **argv) {
    FILE *file;
    hailstone_t hailstones[SIZE];
    char *line;
    size_t sz = 0;
    size_t total = 0;
    hailstone_t left;
    hailstone_t right;
    double x;
    double y;

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
        if (sz >= SIZE) {
            fprintf(stderr, "Too many inputs\n");
            return EXIT_FAILURE;
        }

        hailstones[sz++] = strToHail(line);
        free(line);
    }

    for (size_t i = 0; i < sz; ++i) {
        left = hailstones[i];
        for (size_t j = 0; j < i; ++j) {
            right = hailstones[j];
            double den = left.a * right.b - right.a * left.b;

            if (den == 0.0) {
                continue;
            }

            x = (left.c * right.b - right.c * left.b) / den;
            y = (right.c * left.a - left.c * right.a) / den;

            if (MIN_VAL <= x && x <= MAX_VAL && MIN_VAL <= y && y <= MAX_VAL) {
                if ((x - left.x) * left.vx >= 0.0 &&
                    (y - left.y) * left.vy >= 0.0 &&
                    (x - right.x) * right.vx >= 0.0 &&
                    (y - right.y) * right.vy >= 0.0) {
                    total++;
                }
            }
        }
    }

    printf("%zu\n", total);

    return EXIT_SUCCESS;
}
