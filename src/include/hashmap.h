#ifndef HASHMAP_H
#define HASHMAP_H

#include "list_sl.h" //for bucket data structure
#include "fnv_1a.h" //for hashing function

/* defining the core functionality for a hashmap
    keys will be char pointers, and values will be void pointers
    being kept as simple as possible for now
*/

/* keys are unique, value are not */
typedef struct {
  head_sl **buckets; //an array of lists used to store k-v pairs within buckets
  unsigned long size; //to keep track of size without needing to iterate
  unsigned long used; //keep track of buckets in use
} hashmap;

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

unsigned long fnv_1a(char *key);

#endif
