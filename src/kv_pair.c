#include "include/kv_pair.h"

/* KV_PAIR FUNCTIONS */

//return memory address for a new kv_pair
kv_pair *kv_pair_new(char *key, void *value) {
  //fail if key or value is null
  if (key == NULL || value == NULL) {
    return NULL; //failed
  }

  //allocate memory for a kv_pair struct
  kv_pair *new_pair = (kv_pair *)malloc(sizeof(kv_pair));
  
  //allocate memory for the key
  new_pair->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
  //assign key
  //plus one ensures null termination
  strncpy(new_pair->key, key, strlen(key) + 1);

  //assign value
  new_pair->value = value;

  return new_pair;
}
