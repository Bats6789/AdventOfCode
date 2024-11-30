/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 24 of AOC.
 * Vers: 1.0.0 12/24/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 300

typedef long long int lli;

typedef struct {
    lli x;
    lli y;
    lli z;
    lli vx;
    lli vy;
    lli vz;
} hailstone_t;

hailstone_t strToHail(const char *str) {
    hailstone_t hailstone = {0, 0, 0, 0, 0, 0};

    sscanf(str, "%lld, %lld, %lld @ %lld, %lld, %lld", &hailstone.x,
           &hailstone.y, &hailstone.z, &hailstone.vx, &hailstone.vy,
           &hailstone.vz);

    return hailstone;
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

void printHail(hailstone_t hailstone) {
    printf("%lld, %lld, %lld, @ %lld, %lld, %lld\n", hailstone.x, hailstone.y,
           hailstone.z, hailstone.vx, hailstone.vy, hailstone.vz);
}

void matrixMultiply(double matrix[6][6], double vector[6], double ans[6]) {
    for (size_t i = 0; i < 6; ++i) {
        ans[i] = 0;

        for (size_t j = 0; j < 6; ++j) {
            ans[i] += matrix[i][j] * vector[j];
        }
    }
}

double determinate(size_t width, size_t height, double matrix[height][width]) {
    double ans = 0;
    double tmpMat[height - 1][width - 1];
    size_t tmpW;
	double sign = 1;

    if (width == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    for (size_t k = 0; k < width; ++k) {
        for (size_t i = 0; i < height - 1; ++i) {
			tmpW = 0;
            for (size_t j = 0; j < width - 1; ++j) {
				if (j == k) {
					tmpW++;
				}
                tmpMat[i][j] = matrix[i + 1][tmpW++];
            }
        }

        ans += sign * matrix[0][k] * determinate(width - 1, height - 1, tmpMat);
		sign *= -1;
    }

    return ans;
}

double cofactor(size_t width, size_t height, double matrix[height][width],
                size_t row, size_t col) {
    double tmpMatrix[width - 1][height - 1];
    size_t tmpi = 0;
    size_t tmpj = 0;

    for (size_t i = 0; i < height; ++i) {
        if (i == row) {
            continue;
        }
        tmpj = 0;
        for (size_t j = 0; j < width; ++j) {
            if (j == col) {
                continue;
            }

            tmpMatrix[tmpi][tmpj++] = matrix[i][j];
        }
        tmpi++;
    }

    if ((row + col) % 2 == 0) {
        return determinate(width - 1, height - 1, tmpMatrix);
    } else {
        return -determinate(width - 1, height - 1, tmpMatrix);
    }
}

void adjoint(double matrix[6][6]) {
    double tmpMatrix[6][6];
    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            tmpMatrix[i][j] = cofactor(6, 6, matrix, i, j);
        }
    }

    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            matrix[i][j] = tmpMatrix[i][j];
        }
    }
}

void printMatrix(double matrix[6][6]) {
	for (size_t i = 0; i < 6; ++i) {
		putchar('[');
		for (size_t j = 0; j < 6; ++j) {
			printf("%lf", matrix[i][j]);
			if (j != 5) {
				putchar(',');
				putchar(' ');
			}
		}
		putchar(']');
		putchar('\n');
	}
}


void inverseMatrix(double matrix[6][6]) {
    double det = determinate(6, 6, matrix);

    adjoint(matrix);

	printf("\n%lf\n\n", det);
	printMatrix(matrix);

    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 6; ++j) {
			matrix[i][j] = matrix[i][j] / det;
        }
    }
}

int main(int argc, char **argv) {
    FILE *file;
    hailstone_t hailstones[SIZE];
    char *line;
    size_t sz = 0;
    hailstone_t p1;
    hailstone_t p2;
    hailstone_t p3;
    double ans[6] = {0};
    double con[6] = {0};
    double matrix[6][6] = {0};

    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough inputs\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while ((line = readLine(file)) != NULL) {
        if (sz >= SIZE) {
            fprintf(stderr, "Too many inputs\n");
            return EXIT_FAILURE;
        }

        hailstones[sz++] = strToHail(line);
        free(line);
    }

    p1 = hailstones[0];
    p2 = hailstones[1];
    p3 = hailstones[2];

    con[0] = (p1.vy * p1.x + p2.vx * p2.y) - (p1.vx * p1.y + p2.vy * p2.x);
    con[1] = (p1.vz * p1.y + p2.vy * p2.z) - (p1.vy * p1.z + p2.vz * p2.y);
    con[2] = (p2.vy * p2.x + p3.vx * p3.y) - (p2.vx * p2.y + p3.vy * p3.x);
    con[3] = (p2.vz * p2.y + p3.vy * p3.z) - (p2.vy * p2.z + p3.vz * p3.y);
    con[4] = (p1.vy * p1.x + p3.vx * p3.y) - (p1.vx * p1.y + p3.vy * p3.x);
    con[5] = (p1.vz * p1.y + p3.vy * p3.z) - (p1.vy * p1.z + p3.vz * p3.y);

    matrix[0][0] = p1.vy - p2.vy;
    matrix[0][1] = p2.vx - p1.vx;
    matrix[0][2] = 0;
    matrix[0][3] = p2.y - p1.y;
    matrix[0][4] = p1.x - p2.x;
    matrix[0][5] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = p1.vz - p2.vz;
    matrix[1][2] = p2.vy - p1.vy;
    matrix[1][3] = 0;
    matrix[1][4] = p2.z - p1.z;
    matrix[1][5] = p1.y - p2.y;

    matrix[2][0] = p2.vy - p3.vy;
    matrix[2][1] = p3.vx - p2.vx;
    matrix[2][2] = 0;
    matrix[2][3] = p3.y - p2.y;
    matrix[2][4] = p2.x - p3.x;
    matrix[2][5] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = p2.vz - p3.vz;
    matrix[3][2] = p3.vy - p2.vy;
    matrix[3][3] = 0;
    matrix[3][4] = p3.z - p2.z;
    matrix[3][5] = p2.y - p3.y;

    matrix[4][0] = p1.vy - p3.vy;
    matrix[4][1] = p3.vx - p1.vx;
    matrix[4][2] = 0;
    matrix[4][3] = p3.y - p1.y;
    matrix[4][4] = p1.x - p3.x;
    matrix[4][5] = 0;

    matrix[5][0] = 0;
    matrix[5][1] = p1.vz - p3.vz;
    matrix[5][2] = p3.vy - p1.vy;
    matrix[5][3] = 0;
    matrix[5][4] = p3.z - p1.z;
    matrix[5][5] = p1.y - p3.y;

	printMatrix(matrix);

    inverseMatrix(matrix);

	putchar('\n');
	printMatrix(matrix);

    matrixMultiply(matrix, con, ans);

    printf("%lf\n", ans[0] + ans[1] + ans[2]);

    return EXIT_SUCCESS;
}
