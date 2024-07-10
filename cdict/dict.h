#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16
#define LOAD_FACTOR 0.3

typedef struct Dict Dict;
Dict *new_Dict(int capacity);
Dict *empty_Dict();
char *dictGet(Dict *self, char *value);
void dictSet(Dict *self, char *key, char *value);
void dictRemove(Dict *self, char *key);
char **keys(Dict *self);
char **vals(Dict *self);
void printDict(Dict *self);
void printHashedDict(Dict *self);