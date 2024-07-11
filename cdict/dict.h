#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16
#define LOAD_FACTOR 0.3

typedef struct Dict Dict;
Dict *new_dict(int capacity);
Dict *empty_dict();
char *dict_get(Dict *self, char *value);
void dict_set(Dict *self, char *key, char *value);
void dict_remove(Dict *self, char *key);
char **keys(Dict *self);
char **vals(Dict *self);
void print_dict(Dict *self);
void print_hashed_dict(Dict *self);
