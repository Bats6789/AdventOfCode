/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 5 of AOC.
 * Vers: 1.0.0 12/05/2025 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct range_t {
    unsigned long long start;
    unsigned long long stop;
} range_t;

typedef struct string {
    char *str;
    size_t len;
    size_t cap;
} string_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);

int main(int argc, char **argv) {
    FILE *file;
    range_t *ranges = NULL;
    size_t ranges_cap = 0;
    size_t ranges_sz = 0;
    unsigned long long *ids = NULL;
    size_t ids_cap = 0;
    size_t ids_sz = 0;
    unsigned long long count = 0;
    bool finished_ranges = false;
	string_t line = init_str();

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // allocate ranges
    ranges_cap = 100;
    ranges = malloc(sizeof(*ranges) * ranges_cap);
    if (ranges == NULL) {
        perror("Failed to allocate ranges");
        return EXIT_FAILURE;
    }

    // allocate ids
    ids_cap = 100;
    ids = malloc(sizeof(*ids) * ids_cap);
    if (ids == NULL) {
        perror("Failed to allocate ids");
        return EXIT_FAILURE;
    }

    // collect data
    while (!feof(file)) {
		read_line(file, &line);

		if (line.len == 0) {
			finished_ranges = true;
		} else if (!finished_ranges) {
			sscanf(line.str, "%llu-%llu", &ranges[ranges_sz].start, &ranges[ranges_sz].stop);
            ranges_sz += 1;
            if (ranges_sz >= ranges_cap) {
                ranges_cap *= 2;
                ranges = realloc(ranges, sizeof(*ranges) * ranges_cap);
                if (ranges == NULL) {
                    perror("Failed to reallocate ranges");
                    return EXIT_FAILURE;
                }
            }
        } else {
			sscanf(line.str, "%llu", &ids[ids_sz]);
            ids_sz += 1;
            if (ids_sz >= ids_cap) {
                ids_cap *= 2;
                ids = realloc(ids, sizeof(*ids) * ids_cap);
                if (ids == NULL) {
                    perror("Failed to reallocate ids");
                    return EXIT_FAILURE;
                }
            }
        }
    }

	free_str(&line);

    for (size_t i = 0; i < ids_sz; ++i) {
        for (size_t j = 0; j < ranges_sz; ++j) {
            if (ranges[j].start <= ids[i] && ids[i] <= ranges[j].stop) {
                count += 1;
                break;
            }
        }
    }

    printf("%llu\n", count);

	free(ranges);
	free(ids);

    return EXIT_SUCCESS;
}

string_t init_str(void) {
    string_t str = {NULL, 0, 100};
    str.str = calloc(str.cap, sizeof *str.str);

    return str;
}

void free_str(string_t *str) {
    if (str == NULL) {
        return;
    }

    if (str->str != NULL) {
        free(str->str);
        str->str = NULL;
        str->cap = 0;
        str->len = 0;
    }
}

void read_line(FILE *file, string_t *str) {
    char c;
    str->len = 0;

    if (str->cap == 0) {
        str->cap = 100;
        str->str = calloc(str->cap, sizeof *str->str);
    }

    while ((c = fgetc(file)) != EOF && c != '\n') {
        str->str[str->len++] = c;

        if (str->len >= str->cap) {
            str->cap *= 2;
            str->str = realloc(str->str, sizeof *str->str * str->cap);
        }
    }

    str->str[str->len] = '\0';
}
