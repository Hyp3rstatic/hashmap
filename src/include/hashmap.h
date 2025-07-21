#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h> //for memory management
#include <string.h> //for string utilities

/* defining the core functionality for a hashmap
    keys will be chat pointers, and values will be void pointers
    being kept as simple as possible for now
*/

//for determining types when assigning void pointers in functions
typedef enum {
  INT = 0,
  FLOAT = 1,
  STRING = 2,
} types;

/* struct for a key-value pair */
/* intended only for use in a hashmap */
/* user does not directly interact with when interfacing with hashmap functionality */
typedef struct {
  char *key;
  void *value;
} kv_pair;

//typedefing for code clarity
typedef kv_pair **bucket;

/* keys are unique, value are not */
typedef struct {
  bucket buckets; //an array of arrays to store k-v pairs within buckets
  unsigned long size; //to keep track of size without needing to iterate
  unsigned long used; //keep track of buckets in use
} hashmap;

/* KV_PAIR FUNCTIONS */

//return memory address for a new kv_pair
//type determines which cast is done on the value
kv_pair *kv_pair_new(char *key, void *value, types type);

/* HASHMAP FUNCTIONS */

//return a pointer to a newly initialized hashmap
hashmap *hashmap_new(void);

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

/* extra functions for convenience */

//return the ratio of buckets used to hashmap size
//for resizing checks
float hashmap_ratio(hashmap *map);

#endif

