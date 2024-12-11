/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 11 of AOC.
 * Vers: 1.0.0 12/11/2024 CBW - Original code.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct key {
	size_t value;
	size_t tick;
} key_t;

typedef struct hashmap {
	size_t *values;
	key_t *keys;
	bool *valid;
	size_t sz;
} hashmap_t;

hashmap_t map = {NULL, NULL, NULL, 0};

size_t get_stones(size_t value, size_t tick);
size_t hash(hashmap_t map, key_t key);
bool in(hashmap_t map, key_t key);
size_t get(hashmap_t map, key_t key);
void insert(hashmap_t *map, key_t key, size_t value);

int main(int argc, char **argv) {
    FILE *file;
	size_t total = 0;
	size_t item;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	map.sz = 100000;

	map.values = malloc(sizeof *map.values * map.sz);
	map.keys = malloc(sizeof *map.keys * map.sz);
	map.valid = malloc(sizeof *map.valid * map.sz);

	for (size_t i = 0; i < map.sz; ++i) {
		map.values[i] = 0;
		map.keys[i] = (key_t){0, 0};
		map.valid[i] = false;
	}

	while (fscanf(file, "%zu", &item) != EOF) {
		total += get_stones(item, 75);
	}

	printf("%zu\n", total);

    return EXIT_SUCCESS;
}

size_t get_stones(size_t value, size_t tick) {
	size_t res;
	key_t key = {value, tick};

	if (tick == 0) {
		return 1;
	} 

	if (in(map, key)) {
		return get(map, key);
	}

	if (value == 0) {
		res = get_stones(1, tick - 1);
	} else if ((size_t)(floor(log10(value)) + 1) % 2 == 0) {
		size_t scale = round(pow(10, (floor(log10(value)) + 1) / 2));
		size_t left = value / scale;
		size_t right = value % scale;
		res = get_stones(left, tick - 1) + get_stones(right, tick - 1);
	} else {
		res = get_stones(2024 * value, tick - 1);
	}

	insert(&map, key, res);

	return res;
}

bool in(hashmap_t map, key_t key) {
	size_t index = hash(map, key);
	key_t found = map.keys[index];

	while (found.value != key.value && found.tick != key.tick && !map.valid[index]) {
		if (hash(map, key) != hash(map, found)) {
			break;
		}

		index += 1;
		if (index >= map.sz) {
			index = 0;
		}

		found = map.keys[index];
	}

	return found.value == key.value && found.tick == key.tick;
}

size_t hash(hashmap_t map, key_t key) {
	return (key.value + 1000 * key.tick) % map.sz;
}

size_t get(hashmap_t map, key_t key) {
	size_t index = hash(map, key);
	key_t found = map.keys[index];

	while (found.value != key.value && found.tick != key.tick && map.valid[index]) {
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

void insert(hashmap_t *map, key_t key, size_t value) {
	size_t index = hash(*map, key);
	key_t found = map->keys[index];

	while (found.value != key.value && found.tick != key.tick && map->valid[index]) {
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
