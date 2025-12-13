/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 7 of AOC.
 * Vers: 1.0.0 12/07/2025 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

typedef struct bin_t {
	int *ids;
	unsigned long long *contents;
	size_t sz;
	size_t cap;
} bin_t;

typedef struct dict_t {
	bin_t *bins;
	size_t sz;
} dict_t;

string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);

dict_t init_dict(void);
void store_item(dict_t *dict, int id, unsigned long long content);
size_t hash(dict_t dict, int id);
bool in_dict(dict_t dict, int id);
unsigned long long get_item(dict_t dict, int id);
void copy_dict(dict_t *dest, dict_t *src);
void clear_dict(dict_t *dict);

bin_t init_bin(void);
ssize_t find_id(bin_t bin, int id);
unsigned long long get_content(bin_t bin, int id);
void store_content(bin_t *bin, int id, unsigned long long content);
void copy_bin(bin_t *dest, bin_t *src);
void clear_bin(bin_t *bin);

int main(int argc, char **argv) {
    FILE *file;
	dict_t beams = init_dict();
	dict_t new_beams = init_dict();
	string_t str = init_str();
	unsigned long long count = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	read_line(file, &str);
	for (int i = 0; i < str.len; ++i) {
		if (str.str[i] == 'S') {
			store_item(&beams, i, 1);
		}
	}

	while (!feof(file)) {
		read_line(file, &str);

		if (str.len == 0) {
			continue;
		}

		clear_dict(&new_beams);

		for (size_t i = 0; i < beams.sz; ++i) {
			if (beams.bins[i].ids == NULL) {
				continue;
			}

			bin_t bin = beams.bins[i];
			for (size_t j = 0; j < bin.sz; ++j) {
				if (0 <= bin.ids[j] && bin.ids[j] < str.len && str.str[bin.ids[j]] == '^') {
					if (in_dict(new_beams, bin.ids[j] - 1)) {
						store_item(&new_beams, bin.ids[j] - 1, get_item(new_beams, bin.ids[j] - 1) + bin.contents[j]);
					} else {
						store_item(&new_beams, bin.ids[j] - 1, bin.contents[j]);
					}
					if (in_dict(new_beams, bin.ids[j] + 1)) {
						store_item(&new_beams, bin.ids[j] + 1, get_item(new_beams, bin.ids[j] + 1) + bin.contents[j]);
					} else {
						store_item(&new_beams, bin.ids[j] + 1, bin.contents[j]);
					}
				} else {
					if (in_dict(new_beams, bin.ids[j])) {
						store_item(&new_beams, bin.ids[j], get_item(new_beams, bin.ids[j]) + bin.contents[j]);
					} else {
						store_item(&new_beams, bin.ids[j], bin.contents[j]);
					}
				}
			}
		}
		copy_dict(&beams, &new_beams);
	}

	for (size_t i = 0; i < beams.sz; ++i) {
		bin_t bin = beams.bins[i];

		for (size_t j = 0; j < bin.sz; ++j) {
			count += bin.contents[j];
		}
	}

	printf("%llu\n", count);

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

dict_t init_dict(void) {
	dict_t dict = {NULL, 100};

	dict.bins = malloc(sizeof(*dict.bins) * dict.sz);
	for (size_t i = 0; i < dict.sz; ++i) {
		dict.bins[i] = (bin_t){NULL, NULL, 0, 0};
	}

	return dict;
}

size_t hash(dict_t dict, int id) {
	return id % dict.sz;
}

void store_item(dict_t *dict, int id, unsigned long long content) {
	size_t bin_index = hash(*dict, id);
	if (dict->bins[bin_index].ids == NULL) {
		dict->bins[bin_index] = init_bin();
	}
	store_content(dict->bins + bin_index, id, content);
}

unsigned long long get_item(dict_t dict, int id) {
	size_t bin_index = hash(dict, id);
	return get_content(dict.bins[bin_index], id);
}

bool in_dict(dict_t dict, int id) {
	for (size_t i = 0; i < dict.sz; ++i) {
		if (dict.bins[i].ids != NULL && find_id(dict.bins[i], id) > -1) {
			return true;
		}
	}

	return false;
}

void copy_dict(dict_t *dest, dict_t *src) {
	if (dest->sz < src->sz) {
		dest->sz = src->sz;

		dest->bins = realloc(dest->bins, sizeof(*dest->bins) * dest->sz);
	}

	for (size_t i = 0; i < dest->sz; ++i) {
		if (dest->bins[i].ids == NULL) {
			dest->bins[i] = init_bin();
		}

		copy_bin(dest->bins + i, src->bins + i);
	}
}

void clear_dict(dict_t *dict) {
	for (size_t i = 0; i < dict->sz; ++i) {
		if (dict->bins[i].ids != NULL) {
			clear_bin(dict->bins + i);
		}
	}
}

bin_t init_bin(void) {
	bin_t bin = {NULL, NULL, 0, 100};

	bin.ids = malloc(sizeof(*bin.ids) * bin.cap);
	bin.contents = malloc(sizeof(*bin.contents) * bin.cap);

	return bin;
}

ssize_t find_id(bin_t bin, int id) {
	for (size_t i = 0; i < bin.sz; ++i) {
		if (bin.ids[i] == id) {
			return i;
		}
	}
	return -1;
}

unsigned long long get_content(bin_t bin, int id) {
	ssize_t index = find_id(bin, id);

	return bin.sz > index && index >= 0 ? bin.contents[index] : 0;
}

void store_content(bin_t *bin, int id, unsigned long long content) {
	ssize_t index = find_id(*bin, id);

	if (index < 0) {
		if (bin->sz >= bin->cap) {
			bin->cap *= 2;
			bin->ids = realloc(bin->ids, sizeof(*bin->ids) * bin->cap);
			bin->contents = realloc(bin->contents, sizeof(*bin->contents) * bin->cap);
		}

		bin->ids[bin->sz] = id;
		bin->contents[bin->sz++] = content;
	} else {
		bin->contents[index] = content;
	}
}

void copy_bin(bin_t *dest, bin_t *src) {
	if (dest->cap < src->cap) {
		dest->cap = src->cap;

		dest->ids = realloc(dest->ids, sizeof(*dest->ids) * dest->cap);
		dest->contents = realloc(dest->contents, sizeof(*dest->contents) * dest->cap);
	}

	dest->sz = src->sz;

	memcpy(dest->ids, src->ids, sizeof(*dest->ids) * dest->sz);
	memcpy(dest->contents, src->contents, sizeof(*dest->contents) * dest->sz);
}

void clear_bin(bin_t *bin) {
	bin->sz = 0;
}
