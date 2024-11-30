/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 15 of AOC.
 * Vers: 1.0.0 12/15/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 256
#define NAME_SZ 7

typedef struct {
	char name[NAME_SZ];
	int power;
} contents_t;

typedef struct {
	contents_t contents[100];
	size_t count;
} box_t;

unsigned long long hash(const char *str) {
	unsigned long long value = 0;

	while (*str) {
		value = 17 * (value + *str++);
	}

	return value % SIZE;
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
    FILE *file;
	char *line;
	char *tok;
	char *find;
	unsigned long long ans = 0;
	unsigned long long key = 0;
	box_t boxes[256] = {0};
	bool found;

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

	tok = strtok(line, ",");

	while(tok != NULL){
		find = strchr(tok, '=');
		if (find != NULL) {
			*find = '\0';
			key = hash(tok);
			found = false;

			for (size_t i = 0; i < boxes[key].count && !found; ++i) {
				if (strcmp(boxes[key].contents[i].name, tok) == 0) {
					boxes[key].contents[i].power = atoi(find + 1);
					found = true;
				}
			}

			if (!found) {
				strncpy(boxes[key].contents[boxes[key].count].name, tok, NAME_SZ);
				boxes[key].contents[boxes[key].count++].power = atoi(find + 1);
			}
		} else {
			find = strchr(tok, '-');
			*find = '\0';
			key = hash(tok);
			found = false;
			size_t foundIndex = 0;
			// search for item
			for (size_t i = 0; i < boxes[key].count && !found; ++i) {
				if (strcmp(boxes[key].contents[i].name, tok) == 0) {
					boxes[key].contents[i].power = atoi(find + 1);
					foundIndex = i;
					found = true;
				}
			}

			for (size_t i = foundIndex; i < boxes[key].count - 1 && found; ++i) {
				strncpy(boxes[key].contents[i].name, boxes[key].contents[i + 1].name, NAME_SZ);
				boxes[key].contents[i].power = boxes[key].contents[i + 1].power;
			}
			if (found) {
				boxes[key].count--;
			}
		}
		tok = strtok(NULL, ",");
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < boxes[i].count; ++j) {
			ans += (i + 1) * (j + 1) * boxes[i].contents[j].power;
		}
	}

	printf("%llu\n", ans);

    return EXIT_SUCCESS;
}
