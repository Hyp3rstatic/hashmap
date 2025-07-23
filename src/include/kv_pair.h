#ifndef KV_PAIR_H
#define KV_PAIR_H

#include <stdlib.h> //for memory management
#include <string.h> //for string utilities

/* struct for a key-value pair */
/* intended only for use in a hashmap */
/* user does not directly interact with when interfacing with hashmap functionality */
typedef struct {
  char *key;
  void *value;
} kv_pair;

/* KV_PAIR FUNCTIONS */

//return memory address for a new kv_pair
//type determines which cast is done on the value
kv_pair *kv_pair_new(char *key, void *value);

#endif
