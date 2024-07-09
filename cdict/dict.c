#include "dict.h"

typedef struct bucket {
  char *key;
  char *val;
  struct bucket *next;
} bucket;

bucket *empty_bucket(){
  bucket *b = malloc(sizeof(bucket));
  b -> key = b -> val = b -> next = NULL; 
  return b;
}

bucket *new_bucket(char *k, char *v){
  bucket *b = empty_bucket();
  b -> key = k; b -> val = v;
  return b;
}

int bucketEmpty(bucket* b){
  return b -> key == NULL && b -> val == NULL;
}

uint8_t hash(char *value){
  uint8_t sum = (uint8_t) value[0];
  for(int i = 1; i < strlen(value); i++){
    sum += (10003 * sum) ^ (int) value[i];
  } return sum;
}

typedef struct Dict {
  int filled;
  int capacity;
  bucket contents[];
} Dict;

Dict *new_Dict(int capacity){
  Dict *dict = malloc(capacity * sizeof(bucket));
  dict -> capacity = capacity;
  dict -> filled = 0;
  bucket b_arr[capacity];
  for(int i = 0; i < capacity; i++) 
    b_arr[i] = *empty_bucket();
  memcpy(dict -> contents, b_arr, sizeof(b_arr));
  return dict;
}

Dict *empty_Dict(){
  return new_Dict(DEFAULT_SIZE);
}

bucket *bucketAtVal(Dict *self, char *val){
  return &self -> contents[hash(val) % (self -> capacity)];
}

char *dictGet(Dict *self, char *key){
  bucket *slot = bucketAtVal(self, key);
  if(slot -> next == NULL || strcmp(slot -> key, key) == 0){
    return slot -> val;
  } else { // Chained
    bucket *temp = slot;
    do { // Linear search
      temp = temp -> next;
      if(strcmp(temp -> key, key) == 0) return temp -> val;
    } while(temp -> next != NULL);
    return NULL; // dict[key] does not exist
  }
}

void dictSet(Dict *self, char *key, char *value){
  if((self -> filled + 1) / self -> capacity > LOAD_FACTOR){
    self = realloc(self, sizeof(self) * 2);
    self -> capacity *= 2;
    self -> filled = 0;
  } bucket *slot = bucketAtVal(self, key);
  if(slot -> next == NULL){
    slot -> key = key;
    slot -> val = value;
  } else { // Chain
    bucket *temp = slot;
    while(temp -> next != NULL) temp = temp -> next;
    temp -> next = new_bucket(key, value);
  } self -> filled++; 
}

char **keys(Dict *self){
  char *keys[self -> filled]; int k = 0;
  for(int i = 0; i < self -> capacity; i++){
    bucket *slot = &self -> contents[i];
    if(bucketEmpty(slot) == 0){
      do { keys[k] = slot -> key;
        slot = slot -> next; k++;
      } while(slot != NULL);
    }
  }
}

char **vals(Dict *self){
  char *vals[self -> filled]; int k = 0;
  for(int i = 0; i < self -> capacity; i++){
    bucket *slot = &self -> contents[i];
    if(bucketEmpty(slot) == 0){
      do { vals[k] = slot -> val;
        slot = slot -> next; k++;
      } while(slot != NULL);
    }
  }
}

void dictRemove(Dict *self, char *key){
  bucket *slot = bucketAtVal(self, key);
  if(slot -> next == NULL){
    slot -> key = slot -> val = NULL;
    self -> filled--;
  } else { // Chained - TBD
    bucket *temp = slot; bucket *prev = NULL;
    while(temp -> next != NULL){ // Check to see if work
      if(strcmp(temp -> key, key) == 0){
        if(prev != NULL) prev -> next = temp -> next;
        else slot = temp -> next;
        free(temp); temp = NULL;
        self -> filled--; return;
      } prev = temp; temp = temp -> next;
    }
  }
}

void printDict(Dict *self){
  /*char **k = keys(self); char **v = vals(self);
  for(int i = 0; i < self -> capacity; i++)
    printf("'%s': '%s'\n", k[i], v[i]);
  */
  for(int i = 0; i < self -> capacity; i++){
    bucket *slot = &self -> contents[i];
    if(bucketEmpty(slot) == 0){
      do {
        printf("'%s': '%s'\n", slot -> key, slot -> val);
        slot = slot -> next;
      } while(slot != NULL);
    }
  }
}

void printHashedDict(Dict *self){
  for(int i = 0; i < self -> capacity; i++){
    printf("[%d] -", i);
    bucket *slot = &self -> contents[i];
    if(bucketEmpty(slot) == 0){
      while(slot != NULL){
        printf(" '%s': '%s' -", slot -> key, slot -> val);
        slot = slot -> next;
      }
    } printf("\n");
  }
}