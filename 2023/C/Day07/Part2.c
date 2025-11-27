/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 7 of AOC.
 * Vers: 1.0.0 12/07/2023 CBW - Original code.
 */
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char cards[6];
    int score;
} hand_t;

int map(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else {
        switch (c) {
            case 'A':
                return 14;
                break;
            case 'K':
                return 13;
                break;
            case 'Q':
                return 12;
                break;
            case 'T':
                return 10;
                break;
            default:
                return 0;
        }
    }
}

int getScore(const char cards[6]) {
    int counts[15] = {0};
    int highestCount = 0;
    int twoCount = 0;
    int jCount = 0;
    bool two = false;

    for (int i = 0; i < 5; ++i) {
        counts[map(cards[i])]++;
    }

    // 'J' -> 0
    jCount = counts[0];
    if (jCount >= 4) {
        return 7;
    }

    for (int i = 1; i < 15; ++i) {
        highestCount = counts[i] > highestCount ? counts[i] : highestCount;
        switch (counts[i]) {
            case 2:
                two = true;
                twoCount++;
        }
    }

    switch (highestCount + jCount) {
        case 5:
        case 4:
            return 2 + highestCount + jCount;
            break;
        case 3:
			if(two && jCount == 1){
				twoCount--;
				two = twoCount != 0;
			}
            return two ? 5 : 4;
            break;
        default:
            return 1 + twoCount + jCount;
            break;
    }
}

int cmp(const void *left, const void *right) {
    hand_t l = *(hand_t *)left;
    hand_t r = *(hand_t *)right;
    int lScore = getScore(l.cards);
    int rScore = getScore(r.cards);

    if (lScore != rScore) {
        return lScore - rScore;
    } else {
        for (int i = 0; i < 5; ++i) {
            int lMap = map(l.cards[i]);
            int rMap = map(r.cards[i]);
            if (lMap != rMap) {
                return lMap - rMap;
            }
        }
        return 0;
    }
}

int main(int argc, char **argv) {
    FILE *file;
    hand_t hands[1000];
    size_t count = 0;
    uint64_t score = 0;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (!feof(file) && count < 1000) {
        fscanf(file, "%5s %d", hands[count].cards, &hands[count].score);
        count++;
    }

    qsort(hands, count, sizeof(*hands), cmp);

    for (int i = 0; i < count; ++i) {
        score += (i + 1) * hands[i].score;
    }

    printf("%" PRIu64 "\n", score);

    return EXIT_SUCCESS;
}
