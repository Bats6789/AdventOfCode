/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 19 of AOC.
 * Vers: 1.0.0 12/19/2023 CBW - Original code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int x;
	int m;
	int a;
	int s;
} part_t;

typedef struct {
	char param;
	char cmp;
	int value;
	char result[4];
} op_t;

typedef struct {
	op_t *ops;
	char name[4];
	size_t sz;
	size_t capacity;
} rule_t;

typedef struct {
	rule_t *rules;
	size_t sz;
	size_t capacity;
} rules_t;

part_t strToPart(const char *str) {
	part_t part;

	sscanf(str, "{x=%d,m=%d,a=%d,s=%d}", &part.x, &part.m, &part.a, &part.s);

	return part;
}

op_t strToOp(char *str) {
	op_t op = {'\0', '\0', 0, ""};
	char *split;

	split = strchr(str, ':');

	if (split == NULL) {
		strncpy(op.result, str, 4);
		return op;
	}

	*split++ = '\0';

	op.param = str[0];
	op.cmp = str[1];
	op.value = atoi(str + 2);

	strncpy(op.result, split, 4);

	return op;
}

rule_t strToRule(char *str) {
	rule_t rule = {NULL, "", 0, 10};
	char *tok;

	rule.ops = malloc(sizeof(*rule.ops) * rule.capacity);
	
	tok = strtok(str, "{}");

	strncpy(rule.name, tok, 4);

	str = strtok(NULL, "{}");

	tok = strtok(str, ",");

	while (tok) {
		rule.ops[rule.sz++] = strToOp(tok);

		if (rule.sz >= rule.capacity) {
			rule.capacity *= 2;
			rule.ops = realloc(rule.ops, sizeof(*rule.ops) * rule.capacity);
		}

		tok = strtok(NULL, ",");
	}

	return rule;
}

void addRule(rules_t *rules, rule_t rule) {
	if (rules->sz >= rules->capacity) {
		rules->capacity *= 2;
		rules->rules = realloc(rules->rules, sizeof(*rules->rules) * rules->capacity);
	}

	rules->rules[rules->sz++] = rule;
}

rules_t initRules(void) {
	rules_t rules = {NULL, 0, 100};

	rules.rules = malloc(sizeof(*rules.rules) * rules.capacity);

	return rules;
}

rule_t getRule(rules_t rules, const char name[4]) {
	for (size_t i = 0; i < rules.sz; ++i) {
		if (strcmp(rules.rules[i].name, name) == 0) {
			return rules.rules[i];
		}
	}

	return (rule_t){NULL, 0, 0};
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

bool validOp(part_t part, op_t op) {
	int paramValue = 0;
	switch (op.param) {
		case 'x':
			paramValue = part.x;
			break;
		case 'm':
			paramValue = part.m;
			break;
		case 'a':
			paramValue = part.a;
			break;
		case 's':
			paramValue = part.s;
			break;
	}

	switch (op.cmp) {
		case '>':
			return paramValue > op.value;
		default:
			return paramValue < op.value;
	}
}

bool validPart(rules_t rules, const char name[], part_t part) {
	rule_t rule;

	if (name[1] == '\0') {
		return name[0] == 'A';
	}

	rule = getRule(rules, name);

	for (size_t i = 0; i < rule.sz; ++i) {
		if (rule.ops[i].param == '\0') {
			switch (rule.ops[i].result[0]) {
				case 'A':
					return true;
					break;
				case 'R':
					return false;
					break;
				default:
					return validPart(rules, rule.ops[i].result, part);
					break;
			}
		} else {
			if (validOp(part, rule.ops[i])) {
				return validPart(rules, rule.ops[i].result, part);
			}
		}
	}

	return false;
}

unsigned long long getPartScore(part_t part) {
	return part.x + part.a + part.m + part.s;
}

int main(int argc, char **argv) {
    FILE *file;
	char *line;
	unsigned long long score = 0;
	rules_t rules = initRules();
	rule_t rule;
	part_t part;

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
		rule = strToRule(line);
		addRule(&rules, rule);
		free(line);
	}

	while ((line = readLine(file)) != NULL) {
		part = strToPart(line);
		if (validPart(rules, "in", part)) {
			score += getPartScore(part);
		}
		free(line);
	}

	printf("%llu\n", score);

    return EXIT_SUCCESS;
}
