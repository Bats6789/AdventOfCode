/*
 * Name: Part2.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 2 for day 17 of AOC.
 * Vers: 1.0.0 12/17/2024 CBW - Original code.
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int64_t get_values(int64_t *program, size_t sz, int64_t regA, int64_t regB, int64_t regC);
int64_t get_combo(int64_t val, int64_t regA, int64_t regB, int64_t regC);

int main(int argc, char **argv) {
    FILE *file;
	int64_t regA;
	int64_t regB;
	int64_t regC;
	int64_t *program;
	size_t p_sz = 0;
	size_t p_max = 100;
	int64_t *out;
	size_t out_sz = 0;
	size_t out_max = 100;
	int64_t block;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	fscanf(file, "Register A: %"SCNi64"\nRegister B: %"SCNi64"\nRegister C: %"SCNi64"\n\nProgram: ",
		&regA,
		&regB,
		&regC);

	program = malloc(sizeof *program * p_max);

	while (fscanf(file, "%"SCNi64",", &block) != EOF) {
		program[p_sz++] = block;
		if (p_sz >= p_max) {
			p_max *= 2;
			program = realloc(program, sizeof *program * p_max);
		}
	}

	fclose(file);

	if (p_max > p_sz) {
		p_max = p_sz;
		program = realloc(program, sizeof *program * p_max);
	}

	out = malloc(sizeof *out * out_max);

	regA = get_values(program, p_sz, 0, regB, regC);

	printf("%"PRIi64"\n", regA);

	for (ssize_t i = 0; i < p_sz; ++i) {
		int64_t op = program[i++];
		int64_t val = program[i];

		switch (op) {
			case 0:
				regA = regA / pow(2, get_combo(val, regA, regB, regC));
				break;
			case 1:
				regB = regB ^ val;
				break;
			case 2:
				regB = get_combo(val, regA, regB, regC) % 8;
				break;
			case 3:
				if (regA != 0) {
					i = val - 1;
 				}
				break;
			case 4:
				regB = regB ^ regC;
				break;
			case 5:
				out[out_sz++] = get_combo(val, regA, regB, regC) % 8;
				if (out_sz >= out_max) {
					out_max *= 2;
					out = realloc(out, sizeof *out * out_max);
				}
				break;
			case 6:
				regB = regA / pow(2, get_combo(val, regA, regB, regC));
				break;
			case 7:
				regC = regA / pow(2, get_combo(val, regA, regB, regC));
				break;
		}
	}

	for (size_t i = 0; i < out_sz; ++i) {
		if (program[i] != out[i]) {
			fprintf(stderr, "ERROR: %"PRIi64" != %"PRIi64"\n", program[i], out[i]);
			return EXIT_FAILURE;
		}
	}

	free(out);
	free(program);

    return EXIT_SUCCESS;
}

int64_t get_values(int64_t *program, size_t sz, int64_t regA, int64_t regB, int64_t regC) {
	int64_t chunk = 0;

	if (sz == 0) {
		return regA;
	}

	chunk = program[--sz];

	for (size_t i = 0; i < 8; ++i) {
		int64_t tmp = (regA << 3) + i;
		int64_t check = ((i ^ 4) ^ (tmp >> (i ^ 1))) % 8;

		if (check == chunk) {
			int64_t val = get_values(program, sz, tmp, regB, regC);
			if (val >= 0) {
				return val;
			}
		}
	}

	return -1;
}

int64_t get_combo(int64_t val, int64_t regA, int64_t regB, int64_t regC) {
	switch (val) {
		case 4:
			return regA;
			break;
		case 5:
			return regB;
		case 6:
			return regC;
			break;
		default:
			return val;
			break;
	}
}
