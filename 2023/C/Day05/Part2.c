/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 5 of AOC.
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

uint64_t minSrcMapTable(maps_t table) {
    if (table.maps == NULL) {
        return UINT64_MAX;
    }
    uint64_t val = table.maps[0].src;

    for (size_t i = 1; i < table.sz; ++i) {
        val = val < table.maps[i].src ? val : table.maps[i].src;
    }

    return val;
}

map_t lineToMap(const char *line) {
    map_t map;

    sscanf(line, "%" SCNu64 " %" SCNu64 " %" SCNu64, &map.dst, &map.src,
           &map.span);

    return map;
}

maps_t mapTableMap(maps_t valMap, maps_t table) {
    maps_t answer = {NULL, 10};
    map_t queue[1000];
    map_t current;
    map_t check;
    map_t map;
    size_t queueCount = 0;
    size_t answerCount = 0;
    bool found = false;

    answer.maps = malloc(sizeof(*answer.maps) * answer.sz);

    for (queueCount = 0; queueCount < valMap.sz; ++queueCount) {
        queue[queueCount] = valMap.maps[queueCount];
    }

    while (queueCount) {
        // dequeue el
        current = queue[0];
        queueCount--;
        for (size_t i = 0; i < queueCount; ++i) {
            queue[i] = queue[i + 1];
        }

        // check maps
        found = false;
        for (size_t i = 0; i < table.sz && !found; ++i) {
            check = table.maps[i];
            // The start of the current range is in the check range
            if (check.src <= current.src &&
                current.src < check.src + check.span) {
                // the current range is engulfed by the check range
                if (current.src + current.span <= check.src + check.span) {
                    map.src = check.dst + (current.src - check.src);
                    map.span = current.span;
                    answer.maps[answerCount++] = map;
                    // The current range starts in check, but doesn't end in
                    // check
                } else {
                    // append the portion that is in check
                    map.src = check.dst + (current.src - check.src);
                    map.span = (check.src + check.span) - current.src;
                    answer.maps[answerCount++] = map;

                    // add remaining to be checked
                    map.src = current.src + map.span;
                    map.span = current.span - map.span;
                    queue[queueCount++] = map;
                }
                found = true;
                // The start of the check range is in the current range
            } else if (current.src < check.src &&
                       check.src < current.src + current.span) {
                // the check range is engulfed by the current range
                if (check.src + check.span < current.src + current.span) {
                    // Add processed portion
                    map.src = check.dst;
                    map.span = check.span;
                    answer.maps[answerCount++] = map;

                    // add the section after the processed portion to queue
                    map.src = check.src + check.span;
                    map.span =
                        (current.src + current.span) - (check.src + check.span);
                    queue[queueCount++] = map;

                    // remove processed portion from head
                    current.span = check.src - current.src;

                    // the current range stops before the check range completes
                } else {
                    // Add processed portion
                    map.src = check.dst;
                    map.span = (current.src + current.span) - check.src;
                    answer.maps[answerCount++] = map;

                    // remove processed portion
                    current.span -= map.span;
                }
            }

            if (answerCount >= answer.sz) {
                answer.sz *= 2;
                answer.maps =
                    realloc(answer.maps, sizeof(*answer.maps) * answer.sz);
            }
        }

        // current src couldn't be found in table
        if (!found) {
            answer.maps[answerCount++] = current;

            if (answerCount >= answer.sz) {
                answer.sz *= 2;
                answer.maps =
                    realloc(answer.maps, sizeof(*answer.maps) * answer.sz);
            }
        }
    }

    answer.sz = answerCount;
    answer.maps = realloc(answer.maps, sizeof(*answer.maps) * answer.sz);

    return answer;
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
    uint64_t minLoc;
    uint64_t val;
    size_t count = 0;
    size_t sz = 100;
    maps_t seedToSoil;
    maps_t soilToFert;
    maps_t fertToWater;
    maps_t waterToLight;
    maps_t lightToTemp;
    maps_t tempToHum;
    maps_t humToLoc;
    maps_t valMaps;
    maps_t temp;
    char *line;
    char *tmp;
    char *tok;
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

    // Apply mapping
    for (size_t i = 0; i < count; i += 2) {
        valMaps.maps = malloc(sizeof(*valMaps.maps));
        valMaps.maps[0].src = seeds[i];
        valMaps.maps[0].span = seeds[i + 1];
        valMaps.sz = 1;

        temp = mapTableMap(valMaps, seedToSoil);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, soilToFert);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, fertToWater);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, waterToLight);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, lightToTemp);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, tempToHum);
        free(valMaps.maps);
        valMaps = temp;

        temp = mapTableMap(valMaps, humToLoc);
        free(valMaps.maps);
        valMaps = temp;

        val = minSrcMapTable(valMaps);
        if (firstRead) {
            firstRead = false;
            minLoc = val;
        } else {
            minLoc = val < minLoc ? val : minLoc;
        }
        free(valMaps.maps);
    }

    printf("%" PRIu64 "\n", minLoc);

    return EXIT_SUCCESS;
}
