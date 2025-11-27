/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 2 of AOC.
 * Vers: 1.0.0 12/02/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 1000

typedef struct {
    int ID;
    int maxRed;
    int maxGreen;
    int maxBlue;
} line_t;

int readLine(FILE *file, char buf[LINE_SIZE]) {
    char format[LINE_SIZE];
    snprintf(format, LINE_SIZE, "%%%d[^\n]\n", LINE_SIZE);
    return fscanf(file, format, buf);
}

line_t parseLine(char buf[LINE_SIZE]) {
    line_t line = {0, 0, 0, 0};
    char *tmp = buf;
    int n = 0;
    int num = 0;
    char color = '\0';

    sscanf(tmp, "Game %d: %n", &(line.ID), &n);
    tmp += n;
    while (*tmp != '\0' &&
           sscanf(tmp, "%d %c%*s %n", &num, &color, &n) != EOF) {
        switch (color) {
            case 'r':
                line.maxRed = num > line.maxRed ? num : line.maxRed;
                break;
            case 'g':
                line.maxGreen = num > line.maxGreen ? num : line.maxGreen;
                break;
            case 'b':
                line.maxBlue = num > line.maxBlue ? num : line.maxBlue;
                break;
        }

        tmp += n;
    }

    return line;
}

int main(int argc, char **argv) {
    FILE *file;
    char buf[LINE_SIZE];
    line_t line;
    int sum = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (readLine(file, buf) != EOF) {
        line = parseLine(buf);

        sum += line.maxRed * line.maxGreen * line.maxBlue;
    }

    printf("%d\n", sum);

    return EXIT_SUCCESS;
}
