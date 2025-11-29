/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 6 of AOC.
 * Vers: 1.0.0 12/06/2023 CBW - Original code.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char *tmp;
	char *tok;
	int times[10];
	int distances[10];
	size_t timesSz = 0;
	size_t distancesSz = 0;
	int ans = 1;


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

	tmp = line;
	while( *tmp != ':' ){
		tmp++;
	}
	tmp++;

	tok = strtok(tmp, " ");
	while(tok != NULL){
		times[timesSz++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	free(line);

	line = readLine(file);
	tmp = line;
	while( *tmp != ':' ){
		tmp++;
	}
	tmp++;

	tok = strtok(tmp, " ");
	while(tok != NULL){
		distances[distancesSz++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	free(line);

	for(size_t i = 0; i < timesSz; ++i){
		int t = times[i];
		int d = distances[i];
		int start = ceil(0.5 * (t - sqrt(t * t - 4 * d)));
		int stop = floor(0.5 * (t + sqrt(t * t - 4 * d)));
		ans *= (stop - start + 1);
	}

	printf("%d\n", ans);

    return EXIT_SUCCESS;
}
