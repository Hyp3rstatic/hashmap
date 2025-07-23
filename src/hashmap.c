#include "include/hashmap.h"

/* HASHMAP FUNCTIONS */

//note: the challenge of a hashmap rn is managing the size
//want enough size to not be resizing every insert or removal
//capacity will double when 3/4ths (75%) of capacity is in use
//will not resize when shrinking

//return a a newly initialized hashmap
//initial capacity will be 16 here
hashmap *hashmap_new(void) {
  //allocate hashmap mem
  hashmap *new_map = (hashmap *)malloc(sizeof(hashmap));

  unsigned short size = 16; //default size

  //assign default vals
  new_map->size = size;
  new_map->used = 0;
  new_map->buckets = (list_sl *)malloc(sizeof(list_sl) * size);

  //blank all buckets
  for(unsigned short i = 0; i < new_map->size; i++) {
    new_map->buckets[i] = NULL;
  }

  return new_map;
}

//insert a new key-value pair into a hashmap
//fails if key is already in use
//returns success status
unsigned short hashmap_insert(char *key, void *value, hashmap *map) {

}

//remove a key-value pair from a hashmap by key, does not return removed value
//returns success status
unsigned short hashmap_remove(char *key, hashmap *map) {

}

//access a value in a hashmap by key
void *hashmap_get(char *key, hashmap *map) {
  //NULL checks
  if (key == NULL || map == NULL) {
    return NULL; //err: NULL args
  }

  //hash to bucket index
  unsigned long hash = fnv_1a(key);
  unsigned long idx = hash%map->size;

  //assign head of bucket to search
  list_sl itr = map->buckets[idx];

  //store strlen in var to save time in strncmps
  unsigned long key_len = strlen(key);
  
  //NULL check
  if (itr == NULL) {
    return NULL; //err: pair does not exist
  }

  for(;;) {
    //key found
    if (strncmp(itr->data->key, key, key_len) == 0) {
      return itr->data;
    }
    //NULL check
    if (itr->next == NULL) {
      return NULL; //err: pair does not exist
    }

    //go to next entry
    itr = itr->next;
  }

  return NULL; //err: pair does not exist
}

//remove all key-value pairs in a hashmap
//return success status
unsigned short hashmap_clear(hashmap *map) {

}

//return the ratio of buckets used to hashmap size
//for resizing checks
float hashmap_ratio(hashmap *map) {
  return (map->used/map->size);
}

int main(int argc, char *argv[]) {
  return 0;
}
