#include <stdio.h>
#include "../src/include/hashmap.h"

void print_map(hashmap *map) {
  for(unsigned long i = 0; i < map->size; i++){
    if(map->buckets[i] == NULL) {
      continue;
    }

    printf("[%lu]: ", i);

    node_sl *itr = map->buckets[i];
    for(; itr != NULL; itr = itr->next) {
      printf("{%s: %s} ", itr->data->key, (char *)itr->data->value);
    }
    printf("\n");
  }
}

void test_value(char *key, char *val, hashmap *map) {
  printf("\n");
  char *value_insert = (char *)malloc((strlen(val) + 1) *sizeof(char));
  strncpy(value_insert, val, strlen(val) + 1);
  printf("PRE - USE: %lu CAP: %lu | RAT: %f\n", map->used, map->size, hashmap_ratio(map));
  hashmap_insert(key, (char *)value_insert, map);
  printf("POS - USE: %lu CAP: %lu | RAT: %f\n", map->used, map->size, hashmap_ratio(map));
  char *value_retrieved = (char *)hashmap_get(key, map);
  printf("INS: %s | KEY: %s | RET: %s\n", value_insert, key, (char *)value_retrieved);
  printf("\n");
}

int main(int argc, char *argv[]){

  return 0;
}