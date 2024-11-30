/*
 * Name: Part1.c
 * Auth: Blake Wingard - bats23456789@gmail.com
 * Desc: Part 1 for day 20 of AOC.
 * Vers: 1.0.0 12/20/2023 CBW - Original code.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 60
#define QUEUE_SZ 100

typedef char(name_t)[4];

typedef struct {
    name_t *names;
	bool *states;
    size_t sz;
    size_t cap;
} array_t;

typedef union {
    bool state;
    array_t inputs;
} memory_t;

typedef struct {
    name_t name;
    char type;
    array_t outputs;
    memory_t memory;
} module_t;

typedef struct {
	char origin[13];
	name_t target;
	bool pulse;
} node_t;

typedef struct {
	node_t *nodes;
	size_t sz;
	size_t cap;
} queue_t;

void printArray(array_t array) {
	putchar('[');
	for (size_t i = 0; i < array.sz; ++i) {
		printf("(%s, %c), ", array.names[i], array.states[i] ? 'T' : 'F');
	}
	putchar('\b');
	putchar('\b');
	putchar(']');
	putchar('\n');
}


void printModule(module_t module) {
	printf("name: %s\n", module.name);
	printf("type: %c\n", module.type);
	puts("output:");
	printArray(module.outputs);
	if (module.type == '%') {
		printf("state: %c\n", module.memory.state ? 'T' : 'F');
	} else {
		puts("inputs:");
		printArray(module.memory.inputs);
	}
}


queue_t queueInit(void) {
	queue_t queue = {NULL, 0, 10};

	queue.nodes = malloc(sizeof(*queue.nodes) * queue.cap);

	return queue;
}

void enqueue(queue_t *queue, node_t node) {
	if (queue->sz >= queue->cap) {
		queue->cap *= 2;
		queue->nodes = realloc(queue->nodes, sizeof(*queue->nodes) * queue->cap);
	}

	queue->nodes[queue->sz++] = node;
}

node_t dequeu(queue_t *queue) {
	node_t node = queue->nodes[0];

	queue->sz--;
	for (size_t i = 0; i < queue->sz; ++i) {
		queue->nodes[i] = queue->nodes[i + 1];
	}

	return node;
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

array_t getOutputs(char *str) {
    char *tok;
    array_t array = {NULL, NULL, 0, 10};

    array.names = malloc(sizeof(*array.names) * array.cap);
    array.states = malloc(sizeof(*array.states) * array.cap);

    tok = strtok(str, ", ");
    while (tok) {
        strncpy(array.names[array.sz], tok, 4);
		array.states[array.sz++] = false;
        if (array.sz >= array.cap) {
            array.cap *= 2;
            array.names =
                realloc(array.names, sizeof(*array.names) * array.cap);
            array.states =
                realloc(array.states, sizeof(*array.states) * array.cap);
        }
        tok = strtok(NULL, ", ");
    }

    return array;
}

bool strInArray(const char *str, const array_t array) {
    bool ans = false;

    for (size_t i = 0; i < array.sz && !ans; ++i) {
        if (strcmp(str, array.names[i]) == 0) {
            ans = true;
        }
    }

    return ans;
}

void updateLinks(module_t modules[SIZE], size_t sz) {
    array_t array;
    for (size_t i = 0; i < sz; ++i) {
        if (modules[i].type == '%') {
            modules[i].memory.state = false;
        } else if (modules[i].type == '&') {
            array.sz = 0;
            array.cap = 10;
            array.names = malloc(sizeof(*array.names) * array.cap);
            array.states = malloc(sizeof(*array.states) * array.cap);

            for (size_t j = 0; j < sz; ++j) {
                if (j == i) {
                    continue;
                }

                if (strInArray(modules[i].name, modules[j].outputs)) {
                    strncpy(array.names[array.sz], modules[j].name, 4);
					array.states[array.sz++] = false;

                    if (array.sz >= array.cap) {
                        array.cap *= 2;
                        array.names = realloc(array.names,
                                              sizeof(*array.names) * array.cap);
                        array.states = realloc(array.states,
                                              sizeof(*array.states) * array.cap);
                    }
                }
            }

            modules[i].memory.inputs = array;
        }
    }
}

module_t parseLine(char *line) {
    char *tmp;
    char *tok;
    module_t module;

    module.type = *line;

    tmp = strchr(++line, ' ');
    strncpy(module.name, line, tmp - line);
	module.name[tmp - line] = '\0';

    tmp = strchr(line, '>') + 2;

    module.outputs = getOutputs(tmp);

	if (module.type == '%') {
		module.memory.state = false;
	}

    return module;
}

bool inModules(name_t target, module_t modules[SIZE], size_t sz) {
	bool ans = false;

	for (size_t i = 0; i < sz && !ans; ++i) {
		if (strcmp(target, modules[i].name) == 0) {
			ans = true;
		}
	}

	return ans;
}

size_t getModuleIndex(module_t modules[SIZE], size_t sz, name_t target) {
	for (size_t i = 0; i < sz; ++i) {
		if (strcmp(target, modules[i].name) == 0) {
			return i;
		}
	}

	return SIZE;
}

void updateState(module_t modules[SIZE], size_t index, name_t name, bool state) {
	for (size_t i = 0; i < modules[index].memory.inputs.sz; ++i) {
		if (strcmp(modules[index].memory.inputs.names[i], name) == 0) {
			modules[index].memory.inputs.states[i] = state;
			break;
		}
	}
}

bool checkMemory(memory_t memory) {
	bool ans = false;

	for (size_t i = 0; i < memory.inputs.sz && !ans; ++i) {
		if (!memory.inputs.states[i]) {
			ans = true;
		}
	}

	return ans;
}

void printInputs(name_t input[10], size_t sz) {
	putchar('[');
	for (size_t i = 0; i < sz; ++i) {
		printf("%s, ", input[i]);
	}
	putchar('\b');
	putchar('\b');
	putchar(']');
	putchar('\n');
}

void printModules(module_t modules[SIZE], size_t sz) {
	for (size_t i = 0; i < sz; ++i) {
		printModule(modules[i]);
		putchar('\n');
	}
}

int main(int argc, char **argv) {
    FILE *file;
    char *line;
    char *tmp;
    char *tok;
    name_t broadcastInput[10];
	queue_t queue;
    module_t modules[SIZE];
    size_t count = 0;
    size_t inputCount = 0;
	size_t queueSz;
	size_t modInd = 0;
	unsigned long long lo = 0;
	unsigned long long hi = 0;
	node_t node;

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
        if (*line == 'b') {
            tmp = strchr(line, '>') + 2;
            tok = strtok(tmp, ", ");
            while (tok) {
                strncpy(broadcastInput[inputCount++], tok, 4);
                tok = strtok(NULL, ", ");
            }
        } else {
            modules[count++] = parseLine(line);
        }
    }

    updateLinks(modules, count);

	queue = queueInit();

	for (size_t i = 0; i < 1000; ++i) {
		strcpy(node.origin, "origin");
		node.pulse = false;
		for (size_t j = 0; j < inputCount; ++j) {
			strcpy(node.target, broadcastInput[j]);
			enqueue(&queue, node);
		}

		lo += 1;

		while (queue.sz) {
			node = dequeu(&queue);

			if (node.pulse) {
				hi++;
			} else {
				lo++;
			}

			if (!inModules(node.target, modules, count)) {
				continue;
			}

			modInd = getModuleIndex(modules, count, node.target);

			if (modules[modInd].type == '%') {
				if (!node.pulse) {
					modules[modInd].memory.state = !modules[modInd].memory.state;

					strcpy(node.origin, modules[modInd].name);
					node.pulse = modules[modInd].memory.state;
					for (size_t j = 0; j < modules[modInd].outputs.sz; ++j) {
						strcpy(node.target, modules[modInd].outputs.names[j]);
						enqueue(&queue, node);
					}
				}
			} else {
				updateState(modules, modInd, node.origin, node.pulse);

				bool outgoing = checkMemory(modules[modInd].memory);

				strcpy(node.origin, modules[modInd].name);
				node.pulse = outgoing;
				for (size_t j = 0; j < modules[modInd].outputs.sz; ++j) {
					strcpy(node.target, modules[modInd].outputs.names[j]);
					enqueue(&queue, node);
				}
			}
		}
	}

	printf("%llu\n", lo * hi);

	return EXIT_SUCCESS;
}
