/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 19 of AOC.
 * Vers: 1.0.0 12/19/2024 CBW - Original code.
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct key {
	char *str;
} key_t;

typedef struct hashmap {
	size_t *values;
	key_t *keys;
	bool *valid;
	size_t sz;
} hashmap_t;

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

hashmap_t map = {NULL, NULL, NULL, 0};

size_t valid(char **towels, size_t sz, const char *desired);
string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);
hashmap_t init_hashmap(void);
size_t hash(hashmap_t map, key_t key);
bool in_hashmap(hashmap_t map, key_t key);
size_t hashmap_get(hashmap_t map, key_t key);
void insert_hashmap(hashmap_t *map, key_t key, size_t value);
void free_hashmap(hashmap_t *map);

int main(int argc, char **argv) {
	FILE *file;
	char **towels;
	char *towel_buf;
	char *tok;
	size_t sz = 0;
	size_t count = 0;
	string_t str = init_str();

	if (argc < 2) {
		fprintf(stderr, "ERROR: Not enough inputs\n");
		return EXIT_FAILURE;
	}

	file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	// parse towels
	read_line(file, &str);
	towel_buf = str.str;

	for (char *buf = towel_buf; *buf != '\0'; ++buf) {
		if (*buf == ',') {
			sz++;
		}
	}
	sz++; // account for last element

	towels = malloc(sizeof *towels * sz);

	tok = strtok(towel_buf, ", ");
	while (tok != NULL) {
		towels[count++] = tok;
		tok = strtok(NULL, ", ");
	}

	assert(count == sz);

	map = init_hashmap();

	str = init_str();
	// pass empty line
	read_line(file, &str);

	count = 0;
	while (!feof(file)) {
		read_line(file, &str);

		if (str.len == 0 || str.str[0] == '\0') {
			break;
		}

		count += valid(towels, sz, str.str);
	}

	printf("%zu\n", count);

	fclose(file);
	free_str(&str);
	free(towel_buf);
	free_hashmap(&map);

	return EXIT_SUCCESS;
}

size_t valid(char **towels, size_t sz, const char *desired) {
	key_t key;
	size_t result = 0;
	bool check = false;
	size_t j;

	if (*desired == '\0') {
		return 1;
	}

	key.str = strdup(desired);

	if (in_hashmap(map, key)) {
		result = hashmap_get(map, key);
		free(key.str);
		return result;
	}

	for (size_t i = 0; i < sz; ++i) {
		check = true;
		for (j = 0; towels[i][j] != '\0' &&
		desired[j] != '\0' && check != false; ++j) {
			if (towels[i][j] != desired[j]) {
				check = false;
			}
		}

		if (desired[j] == '\0' && towels[i][j] != '\0') {
			check = false;
		}

		if (check == true) {
			result += valid(towels, sz, desired + j);
			insert_hashmap(&map, key, true);
		}
	}

	insert_hashmap(&map, key, result);
	return result;
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

	str->str[str->len++] = '\0';
}

hashmap_t init_hashmap(void) {
	hashmap_t hashmap;

	hashmap.sz = 100000;
	hashmap.values = malloc(sizeof *hashmap.values * hashmap.sz);
	assert(hashmap.values != NULL);
	hashmap.keys = malloc(sizeof *hashmap.keys * hashmap.sz);
	assert(hashmap.keys != NULL);
	hashmap.valid = malloc(sizeof *hashmap.valid * hashmap.sz);
	assert(hashmap.valid != NULL);

	for (size_t i = 0; i < hashmap.sz; ++i) {
		hashmap.values[i] = false;
		hashmap.valid[i] = false;
		hashmap.keys[i].str = NULL;
	}

	return hashmap;
}

bool in_hashmap(hashmap_t map, key_t key) {
	size_t index = hash(map, key);
	key_t found = map.keys[index];

	if (!map.valid[index]) {
		return false;
	}

	while (map.valid[index] && strcmp(found.str, key.str) != 0) {
		if (hash(map, key) != hash(map, found)) {
			break;
		}

		index += 1;
		if (index >= map.sz) {
			index = 0;
		}

		found = map.keys[index];
	}

	return map.valid[index] && strcmp(found.str, key.str) == 0;
}

size_t hash(hashmap_t map, key_t key) {
	size_t hash_val = 5381;

	for (char *c = key.str; *c != '\0'; ++c) {
		hash_val = ((hash_val << 5) + hash_val) + *c;
	}

	return hash_val % map.sz;
}

size_t hashmap_get(hashmap_t map, key_t key) {
	size_t index = hash(map, key);
	key_t found = map.keys[index];

	while (strcmp(found.str, key.str) != 0) {
		if (hash(map, key) != hash(map, found)) {
			break;
		}

		index += 1;
		if (index >= map.sz) {
			index = 0;
		}

		found = map.keys[index];
	}

	return index < map.sz ? map.values[index] : 0;
}

void insert_hashmap(hashmap_t *map, key_t key, size_t value) {
	size_t index = hash(*map, key);
	key_t found = map->keys[index];

	while (map->valid[index] && strcmp(found.str, key.str) != 0) {
		if (hash(*map, key) != hash(*map, found)) {
			break;
		}

		index += 1;
		if (index >= map->sz) {
			index = 0;
		}

		found = map->keys[index];
	}

	map->values[index] = value;
	map->keys[index] = key;
	map->valid[index] = true;
}

void free_hashmap(hashmap_t *map) {
	if (map == NULL) {
		return;
	}

	if (map->valid != NULL) {
		free(map->valid);
		map->valid = NULL;
	}

	if (map->values != NULL) {
		free(map->values);
		map->values = NULL;
	}

	if (map->keys != NULL) {
		for (size_t i = 0; i < map->sz; ++i) {
			free(map->keys[i].str);
		}
		free(map->keys);
	}
}
