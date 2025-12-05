/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 5 of AOC.
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
bool contains(range_t dest, range_t src);

int main(int argc, char **argv) {
	FILE *file;
	range_t *ranges = NULL;
	size_t ranges_cap = 0;
	size_t ranges_sz = 0;
	range_t *com_ranges = NULL;
	size_t com_ranges_cap = 0;
	size_t com_ranges_sz = 0;
	unsigned long long count = 0;
	bool did_compress = false;
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

	// collect data
	while (!feof(file)) {
		read_line(file, &line);

		if (line.len == 0) {
			break;
		}

		sscanf(line.str, "%llu-%llu", &ranges[ranges_sz].start,
		 &ranges[ranges_sz].stop);
		ranges_sz += 1;
		if (ranges_sz >= ranges_cap) {
			ranges_cap *= 2;
			ranges = realloc(ranges, sizeof(*ranges) * ranges_cap);
			if (ranges == NULL) {
				perror("Failed to reallocate ranges");
				return EXIT_FAILURE;
			}
		}
	}

	free_str(&line);
	fclose(file);

	// allocate com_ranges
	com_ranges_cap = ranges_cap;
	com_ranges = malloc(sizeof(*com_ranges) * com_ranges_cap);
	if (com_ranges == NULL) {
		perror("Failed to allocate com_ranges");
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < ranges_sz; ++i) {
		do {
			did_compress = false;
			for (size_t j = 0; j < com_ranges_sz; ++j) {
				if (contains(com_ranges[j], ranges[i]) ||
					contains(ranges[i], com_ranges[j])) {
					ranges[i].start = ranges[i].start < com_ranges[j].start ? ranges[i].start : com_ranges[j].start;
					ranges[i].stop = ranges[i].stop > com_ranges[j].stop ? ranges[i].stop : com_ranges[j].stop;
					for (size_t k = j; k < com_ranges_sz; ++k) {
						com_ranges[k] = com_ranges[k + 1];
					}
					com_ranges_sz -= 1;
					did_compress = true;
					break;
				}
			}

			if (!did_compress) {
				com_ranges[com_ranges_sz++] = ranges[i];
			}
		} while (did_compress);
	}

	for (size_t i = 0; i < com_ranges_sz; ++i) {
		count += com_ranges[i].stop - com_ranges[i].start + 1;
	}

	printf("%llu\n", count);

	free(ranges);
	free(com_ranges);

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

bool contains(range_t dest, range_t src) {
	return (dest.start <= src.start && src.start <= dest.stop) ||
	(dest.start <= src.stop && src.stop <= dest.stop);
}
