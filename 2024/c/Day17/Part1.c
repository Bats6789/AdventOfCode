/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 17 of AOC.
 * Vers: 1.0.0 12/17/2024 CBW - Original code.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_combo(int val, int regA, int regB, int regC);

int main(int argc, char **argv) {
    FILE *file;
	int regA;
	int regB;
	int regC;
	int *program;
	size_t p_sz = 0;
	size_t p_max = 100;
	int *out;
	size_t out_sz = 0;
	size_t out_max = 100;
	int block;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	fscanf(file, "Register A: %d\nRegister B: %d\nRegister C: %d\n\nProgram: ",
		&regA,
		&regB,
		&regC);

	program = malloc(sizeof *program * p_max);

	while (fscanf(file, "%d,", &block) != EOF) {
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

	for (ssize_t i = 0; i < p_sz; ++i) {
		int op = program[i++];
		int val = program[i];

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
		putchar(out[i] + '0');
		putchar(i + 1 == out_sz ? '\n' : ',');
	}

	free(out);
	free(program);

    return EXIT_SUCCESS;
}

int get_combo(int val, int regA, int regB, int regC) {
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
