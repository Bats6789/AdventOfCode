/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 4 of AOC.
 * Vers: 1.0.0 12/04/2023 CBW - Original code.
 */
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define REPEAT_SZ 100

typedef struct {
    int *winningNumbers;
    int *numbers;
    size_t winningNumbersSz;
    size_t numbersSz;
} scratchCard_t;

typedef struct {
    scratchCard_t *cards;
    size_t sz;
} scratchCards_t;

typedef enum { id, winningNumbers, numbers } readState_t;

uint64_t getScore(scratchCard_t card) {
    uint64_t score = 0;

    for (size_t i = 0; i < card.numbersSz; ++i) {
        for (size_t j = 0; j < card.winningNumbersSz; ++j) {
            if (card.numbers[i] == card.winningNumbers[j]) {
                score++;
                break;
            }
        }
    }

    return score;
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

scratchCard_t lineToScratchCard(const char *line) {
    scratchCard_t card = {NULL, NULL, 10, 10};
    readState_t readState = id;
    int n;
    int tmp;
    size_t count = 0;

    card.winningNumbers =
        malloc(sizeof(*card.winningNumbers) * card.winningNumbersSz);
    card.numbers = malloc(sizeof(*card.numbers) * card.numbersSz);

    while (*line) {
        if (readState == id) {
            if (*line == ':') {
                readState = winningNumbers;
            }
        } else if (readState == winningNumbers) {
            if (*line == '|') {
                card.winningNumbersSz = count;
                readState = numbers;
                count = 0;
            } else if (isdigit(*line)) {
                sscanf(line, "%d%n", &tmp, &n);
                line += n - 1;

                card.winningNumbers[count++] = tmp;

                if (count >= card.winningNumbersSz) {
                    card.winningNumbersSz *= 2;
                    card.winningNumbers = realloc(
                        card.winningNumbers,
                        sizeof(*card.winningNumbers) * card.winningNumbersSz);
                }
            }
        } else {
            sscanf(line, "%d%n", &tmp, &n);
            line += n - 1;

            card.numbers[count++] = tmp;

            if (count >= card.numbersSz) {
                card.numbersSz *= 2;
                card.numbers = realloc(card.numbers,
                                       sizeof(*card.numbers) * card.numbersSz);
            }
        }
        line++;
    }

    card.numbersSz = count;

    return card;
}

scratchCards_t fileToScratchCards(FILE *file) {
    scratchCards_t scratchCards = {NULL, 10};
    size_t count = 0;
    char *line;

    scratchCards.cards = malloc(sizeof(*scratchCards.cards) * scratchCards.sz);

    while ((line = readLine(file)) != NULL) {
        scratchCards.cards[count++] = lineToScratchCard(line);

        if (count >= scratchCards.sz) {
            scratchCards.sz *= 2;
            scratchCards.cards =
                realloc(scratchCards.cards,
                        sizeof(*scratchCards.cards) * scratchCards.sz);
        }

        free(line);
    }

    scratchCards.sz = count;

    return scratchCards;
}

int popArray(int array[REPEAT_SZ]) {
    int pop = array[0];

    for (size_t i = 0; i < 99; ++i) {
        array[i] = array[i + 1];
    }

    return pop;
}

int main(int argc, char **argv) {
    FILE *file;
    scratchCards_t scratchCards;
    uint64_t total = 0;
    uint64_t scratchCardCount = 0;
    uint64_t score = 0;
    int repeatList[REPEAT_SZ] = {0};

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    scratchCards = fileToScratchCards(file);

    for (size_t i = 0; i < scratchCards.sz; ++i) {
        scratchCardCount = 1 + popArray(repeatList);

        score = getScore(scratchCards.cards[i]);

        for (uint64_t i = 0; i < score; ++i) {
            repeatList[i] += scratchCardCount;
        }

        total += scratchCardCount;
    }

    printf("%" PRIu64 "\n", total);

    return EXIT_SUCCESS;
}
