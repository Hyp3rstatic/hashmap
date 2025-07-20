#ifndef HASHMAP_H
#define HASHMAP_H

/* defining the core functionality for a hashmap
    keys will be chat pointers, and values will be void pointers
    being kept as simple as possible for now
*/

/* struct for a key-value pair */
/* intended only for use in a hashmap */
/* user does not directly interact with when interfacing with hashmap functionality */
typedef struct kv_pair{
  char *key;
  void *value;
}kv_pair;

/* keys are unique, value are not */
typedef struct hashmap {
/* def for hashmap here */
}hashmap;

/* KV_PAIR FUNCTIONS */

//return memory address for a new kv_pair
kv_pair *kv_pair_new(char *key, void *value);

/* HASHMAP FUNCTIONS */

//return a pointer to a newly initialized hashmap
hashmap *hashmap_new(void);

//insert a new key-value pair into a hashmap
//fails if key is already in use
//returns success status
unsigned int hashmap_insert(char *key, void *value, hashmap *map);

//remove a key-value pair from a hashmap by key, does not return removed value
//returns success status
unsigned int hashmap_remove(char *key, hashmap *map);

//access a value in a hashmap by key
void *hashmap_get(char *key, hashmap *map);

//remove all key-value pairs in a hashmap
//return success status
unsigned int hashmap_clear(hashmap *map);

#endif

