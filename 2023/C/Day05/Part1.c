/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 5 of AOC.
 * Vers: 1.0.0 12/05/2023 CBW - Original code.
 */
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t dst;
    uint64_t src;
    uint64_t span;
} map_t;

typedef struct {
    map_t *maps;
    size_t sz;
} maps_t;

void printTable(maps_t table) {
    map_t tmp;

    for (int i = 0; i < table.sz; ++i) {
        tmp = table.maps[i];
        printf("{%" PRIu64 ", %" PRIu64 ", %" PRIu64 "}\n", tmp.dst, tmp.src,
               tmp.span);
    }
}

map_t lineToMap(const char *line) {
    map_t map;

    sscanf(line, "%" SCNu64 " %" SCNu64 " %" SCNu64, &map.dst, &map.src,
           &map.span);

    return map;
}

uint64_t mapTableVal(uint64_t val, maps_t table) {
    map_t tmp;
    for (size_t i = 0; i < table.sz; ++i) {
        tmp = table.maps[i];
        if (tmp.src <= val && val < tmp.src + tmp.span) {
            val = tmp.dst + (val - tmp.src);
            break;
        }
    }

    return val;
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

maps_t readMapsTable(FILE *file) {
    char *line = NULL;
    maps_t table = {NULL, 10};
    size_t count = 0;

    line = readLine(file);  // header
    free(line);

    table.maps = malloc(sizeof(*table.maps) * table.sz);
    while ((line = readLine(file)) != NULL && line[0] != '\n') {
        table.maps[count++] = lineToMap(line);

        if (count >= table.sz) {
            table.sz *= 2;
            table.maps = realloc(table.maps, sizeof(*table.maps) * table.sz);
        }
        free(line);
        line = NULL;
    }
    if (line != NULL) {
        free(line);
    }

    table.sz = count;
    table.maps = realloc(table.maps, sizeof(*table.maps) * table.sz);

    return table;
}

int main(int argc, char **argv) {
    FILE *file;
    uint64_t *seeds;
    size_t count = 0;
    size_t sz = 100;
    maps_t seedToSoil;
    maps_t soilToFert;
    maps_t fertToWater;
    maps_t waterToLight;
    maps_t lightToTemp;
    maps_t tempToHum;
    maps_t humToLoc;
    char *line;
    char *tmp;
    char *tok;
    uint64_t minLoc;
    uint64_t val;
    bool firstRead = true;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // parse seeds
    line = readLine(file);
    tmp = line;

    // move to first digit
    while (*tmp != ':') {
        tmp++;
    }
    tmp += 2;

    // process list of seeds
    tok = strtok(tmp, " ");

    seeds = malloc(sizeof(*seeds) * sz);
    while (tok != NULL) {
        sscanf(tok, "%" SCNu64, seeds + count++);

        if (count >= sz) {
            sz *= 2;
            seeds = realloc(seeds, sizeof(*seeds) * sz);
        }

        tok = strtok(NULL, " ");
    }
    free(line);

    // parse empty line
    line = readLine(file);
    free(line);

    // parse tables
    seedToSoil = readMapsTable(file);
    soilToFert = readMapsTable(file);
    fertToWater = readMapsTable(file);
    waterToLight = readMapsTable(file);
    lightToTemp = readMapsTable(file);
    tempToHum = readMapsTable(file);
    humToLoc = readMapsTable(file);

	// Apply mappings
    for (size_t i = 0; i < count; ++i) {
        val = seeds[i];
        val = mapTableVal(val, seedToSoil);
        val = mapTableVal(val, soilToFert);
        val = mapTableVal(val, fertToWater);
        val = mapTableVal(val, waterToLight);
        val = mapTableVal(val, lightToTemp);
        val = mapTableVal(val, tempToHum);
        val = mapTableVal(val, humToLoc);

        if (firstRead) {
            firstRead = false;
            minLoc = val;
        } else {
            minLoc = val < minLoc ? val : minLoc;
        }
    }

    printf("%" PRIu64 "\n", minLoc);

    return EXIT_SUCCESS;
}
