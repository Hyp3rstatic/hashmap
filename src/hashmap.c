#include "include/hashmap.h"

//NOTE: for the outlining an 2D array is used for the buckets
//after adding a linked list implementation an array of linked lists will be used instead
//this is because linked lists offer better performance when adding and removing from buckets

/* KV_PAIR FUNCTIONS */

//return memory address for a new kv_pair
kv_pair *kv_pair_new(char *key, void *value, types type) {
  //fail if key or value is null
  if (key == NULL || value == NULL) {
    return NULL; //failed
  }
  //fail if type is invalid - hopefully a temp check
  if (type < 0 || type > 2) {
    return NULL; //failed
  }
  //allocate memory for a kv_pair struct
  kv_pair *new_pair = (kv_pair *)malloc(sizeof(kv_pair));
  
  //allocate memory for the key
  new_pair->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
  //assign key
  //plus one ensures null termination
  strncpy(new_pair->key, key, strlen(key) + 1);

  //for string values
  if (type == STRING) {
    new_pair->value = (void *)malloc((strlen(value) + 1) * sizeof(char));
    //plus one ensures null termination
    strncpy(new_pair->value, value, strlen(value) + 1);
  }
  //for non-string values
  else {
    //allocate memory for the value
    new_pair->value = (void *)malloc(sizeof(value));
    //assign value
    //TODO: handle assigning value to any types later
    switch (type) {
      default: //just treat it like an int for now (prior check should elim this option anyhow)
      case INT:
        *(int *)new_pair->value = *(int *)value;
        break;
      case FLOAT:
        *(float *)new_pair->value = *(float *)value;
        break;
    }
  }

  return new_pair;
}

/* HASHMAP FUNCTIONS */

//note: the challenge of a hashmap rn is managing the size
//want enough size to not be resizing every insert or removal
//will expand size when 3/4ths (75%) of capacity is in use
//will not resize when shrinking

//return a a newly initialized hashmap
//initial capacity will be 16 here
hashmap *hashmap_new(void) {
  //allocate hashmap mem
  hashmap *new_map = (hashmap *)malloc(sizeof(hashmap));

  unsigned short size = 16; //default size

  //assign default vals
  new_map->size = 16;
  new_map->used = 0;
  new_map->buckets = (bucket)malloc(sizeof(kv_pair *) * size);

  //blank all buckets
  for(unsigned short i = 0; i < new_map->size; i++) {
    new_map->buckets[i] = NULL;
  }

  return new_map;
}

//insert a new key-value pair into a hashmap
//fails if key is already in use
//returns success status
unsigned short hashmap_insert(char *key, void *value, hashmap *map);

//remove a key-value pair from a hashmap by key, does not return removed value
//returns success status
unsigned short hashmap_remove(char *key, hashmap *map);

//access a value in a hashmap by key
void *hashmap_get(char *key, hashmap *map);

//remove all key-value pairs in a hashmap
//return success status
unsigned short hashmap_clear(hashmap *map);

//return the ratio of buckets used to hashmap size
//for resizing checks
float hashmap_ratio(hashmap *map) {
  return (map->used/map->size);
}

int main(int argc, char *argv[]) {
  return 0;
}
