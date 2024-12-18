/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 14 of AOC.
 * Vers: 1.0.0 12/14/2024 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct string {
	char *str;
	size_t len;
	size_t cap;
} string_t;

typedef struct point {
	int x;
	int y;
} point_t;

typedef struct robot {
	point_t pos;
	point_t vel;
} robot_t;

int width = 101;
int height = 103;

point_t move(point_t pos, point_t vel);
string_t init_str(void);
void free_str(string_t *str);
void read_line(FILE *file, string_t *str);

int main(int argc, char **argv) {
    FILE *file;
	size_t robot_sz = 0;
	size_t robot_max = 100;
	size_t tl = 0;
	size_t tr = 0;
	size_t bl = 0;
	size_t br = 0;
	robot_t *robots = NULL;
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

	if (argc == 4) {
		width = atoi(argv[2]);
		height = atoi(argv[3]);
	}

	robots = malloc(sizeof *robots * robot_max);

	while (!feof(file)) {
		robot_t robot;
		read_line(file, &str);

		if (str.len == 0 || str.str[0] == '\0') {
			continue;
		}

		sscanf(str.str, "p=%d,%d v=%d,%d",
										 &robot.pos.x,
										 &robot.pos.y,
										 &robot.vel.x,
										 &robot.vel.y);
		robots[robot_sz++] = robot;

		if (robot_sz >= robot_max) {
			robot_max *= 2;
			robots = realloc(robots, sizeof *robots * robot_max);
		}
	}

	for (size_t i = 0; i < 100; ++i) {
		for (size_t j = 0; j < robot_sz; ++j) {
			robots[j].pos = move(robots[j].pos, robots[j].vel);
		}
	}

	for (size_t i = 0; i < robot_sz; ++i) {
		point_t pos = robots[i].pos;

		if (pos.x < width / 2 && pos.y < height / 2) {
			tl += 1;
		} else if (pos.x < width / 2 && pos.y > height / 2) {
			bl += 1;
		} else if (pos.x > width / 2 && pos.y < height / 2) {
			tr += 1;
		} else if (pos.x > width / 2 && pos.y > height / 2) {
			br += 1;
		}
	}

	printf("%zu\n", tl * bl * tr * br);

	fclose(file);
	free_str(&str);
	free(robots);

    return EXIT_SUCCESS;
}

point_t move(point_t pos, point_t vel) {
	pos.x += vel.x;
	pos.y += vel.y;

	if (pos.x < 0) {
		pos.x += width;
	} else if (pos.x >= width) {
		pos.x -= width;
	}

	if (pos.y < 0) {
		pos.y += height;
	} else if (pos.y >= height) {
		pos.y -= height;
	}

	return pos;
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
