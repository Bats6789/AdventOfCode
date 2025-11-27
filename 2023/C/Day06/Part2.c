/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 6 of AOC.
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

int reverseNum(int num){
	int ans;

	while(num){
		ans = ans * 10 + num % 10;
		num /= 10;
	}

	return ans;
}

int main(int argc, char **argv) {
    FILE *file;
	char *line;
	char *tmp;
	char *tok;
	long long int time = 0;
	long long int distance = 0;
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
		int num = atoi(tok);
		num = reverseNum(num);
		while(num){
			time = time * 10 + num % 10;
			num /= 10;
		}
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
		int num = atoi(tok);
		num = reverseNum(num);
		while(num){
			distance = distance * 10 + num % 10;
			num /= 10;
		}
		tok = strtok(NULL, " ");
	}

	free(line);

	int start = ceil(0.5 * (time - sqrt(time * time - 4 * distance)));
	int stop = floor(0.5 * (time + sqrt(time * time - 4 * distance)));
	ans *= (stop - start + 1);

	printf("%d\n", ans);

    return EXIT_SUCCESS;
}
