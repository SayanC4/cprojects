#include "dict.h"

typedef struct Bucket {
  char *key;
  char *val;
  struct Bucket *next;
} Bucket;

Bucket *empty_bucket(){
  Bucket *b = malloc(sizeof(Bucket));
  b -> key = b -> val = NULL; 
  b -> next = NULL; 
  return b;
}

Bucket *new_bucket(char *k, char *v){
  Bucket *b = empty_bucket();
  b -> key = k; b -> val = v;
  return b;
}

int bucket_empty(Bucket *b){
  return b -> key == NULL && b -> val == NULL;
}

uint8_t hash(char *value){ 
  uint8_t sum = (uint8_t) value[0];
  for(int i = 1; i < strlen(value); i++){
    sum += (10003 * sum) ^ (int) value[i];
  } return sum;
} // a: 1, ... o: 15, p: 0, q: 1, ... z: 10

typedef struct Dict {
  int filled;
  int capacity;
  Bucket contents[];
} Dict;

Dict *new_dict(int capacity){
  Dict *dict = malloc(capacity * sizeof(Bucket));
  dict -> capacity = capacity;
  dict -> filled = 0;
  Bucket b_arr[capacity];
  for(int i = 0; i < capacity; i++) b_arr[i] = *empty_bucket();
  memcpy(dict -> contents, b_arr, sizeof(b_arr));
  return dict;
}

Dict *empty_dict(){
  return new_dict(DEFAULT_SIZE);
}

Bucket *bucket_at_val(Dict *self, char *val){
  return &self -> contents[hash(val) % (self -> capacity)];
}

char *dict_get(Dict *self, char *key){
  Bucket *slot = bucket_at_val(self, key);
  if(slot -> next == NULL || strcmp(slot -> key, key) == 0){
    return slot -> val;
  } else { Bucket *temp = slot;
    do { // Linear search
      temp = temp -> next;
      if(strcmp(temp -> key, key) == 0) return temp -> val;
    } while(temp -> next != NULL);
    return NULL; // dict[key] does not exist
  }
}

void dict_set(Dict *self, char *key, char *value){ 
  if((self -> filled + 1) / self -> capacity > LOAD_FACTOR){  // Untested
    int captemp = self -> capacity; self -> capacity *= 2;
    size_t csz = sizeof(Bucket) * self -> capacity;
    Bucket contemps[captemp] = self -> contents;
    self -> contents = (Bucket*) realloc(self -> contents, csz);
    Bucket *curr; 
    for(int i = 0; i < captemp; i++){
      curr = contemps[i]; 
      if(!bucket_empty(curr){
        do {
          dict_set(self, curr -> key, curr -> val);
          curr = curr -> next;
        } while(curr != NULL);
      }
    }                                                         // Untested
  } Bucket *slot = bucket_at_val(self, key); int cmp = 1; 
  if(slot -> key != NULL) cmp = strcmp(slot -> key, key);
  if(bucket_empty(slot) || (slot -> key != NULL && cmp == 0)){
    slot -> key = key;
    slot -> val = value;
  } else { Bucket *temp = slot;
    while(temp -> next != NULL) temp = temp -> next;
    temp -> next = new_bucket(key, value);
  } self -> filled++; 
}

void dict_remove(Dict *self, char *key){
  Bucket *slot = bucket_at_val(self, key);
  if(slot -> next == NULL){
    slot -> key = slot -> val = NULL;
    self -> filled--;
  } else { 
    Bucket *temp = slot; Bucket *prev = NULL;
    while(temp -> next != NULL){           // Untested
      if(strcmp(temp -> key, key) == 0){
        if(prev != NULL) prev -> next = temp -> next;
        else slot = temp -> next;
        free(temp); temp = NULL;
        self -> filled--; return;
      } prev = temp; temp = temp -> next;  // Untested
    }
  }
}

char **keys(Dict *self){
  char *keys[self -> filled];
  for(int i = 0; i < self -> filled; i++){
    Bucket *slot = &self -> contents[i];
    if(!bucket_empty(slot)){
      do { keys[i++] = slot -> key;
        slot = slot -> next;
      } while(slot != NULL);
    }
  }
}

char **vals(Dict *self){      // Untested
  char *vals[self -> filled];
  for(int i = 0; i < self -> filled; i++){
    Bucket *slot = &self -> contents[i];
    if(!bucket_empty(slot)){
      do { vals[i++] = slot -> val;
        slot = slot -> next;
      } while(slot != NULL);
    }
  }
}

void print_dict(Dict *self){   // Untested
  for(int i = 0; i < self -> filled; i++){
    Bucket *slot = &self -> contents[i];
    if(!bucket_empty(slot)){
      do {
        printf("'%s': '%s'\n", slot -> key, slot -> val);
        slot = slot -> next;
      } while(slot != NULL);
    }
  }
}

void print_hashed_dict(Dict *self){
  for(int i = 0; i < self -> capacity; i++){
    printf("[%d] -", i);
    Bucket *slot = &self -> contents[i];
    if(!bucket_empty(slot)){
      while(slot != NULL){
        printf(" '%s': '%s' -", slot -> key, slot -> val);
        slot = slot -> next;
      }
    } printf("\n");
  }
}
