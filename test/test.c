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
      printf("CREATING NEW HASHMAP\n");
  hashmap *map = hashmap_new();

  test_value("dogs", "woof", map);
  test_value("dogs", "meow", map);//shouldn't update
  test_value("butter", "milk", map);
  test_value("woopie", "cushion", map);
  test_value("strawberry", "lemonade", map);
  test_value("womps", "fortress", map);
  test_value("eric", "cartman", map);
  test_value("harold", "crayon", map);
  test_value("mister", "E", map);
  test_value("timothy", "himsle", map);
  test_value("wegot", "those", map);
  test_value("tony", "hawk", map);
  test_value("kick", "flip", map);
  test_value("loof", "laws", map);
  test_value("apple", "comp", map);
  test_value("surf", "board", map);
  test_value("happy", "golucky", map);
  test_value("think", "tdm", map);
  test_value("whats", "up", map);
  test_value("hold", "that", map);
  //at capacity ^^^

  test_value("Iaint", "scared", map);

  printf("retrieved: %s\n", (char *)hashmap_get("dogs", map));

  test_value("go", "away", map);
  test_value("program", "language", map);
  test_value("ihate", "work", map);

  //none should update down below

  test_value("dogs", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("dogs", "BBBBBBBBBBBBBBBBBBBBBBBB", map);
  test_value("butter", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("woopie", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("strawberry", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("womps", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("eric", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("harold", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("mister", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("timothy", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("wegot", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("tony", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("kick", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("loof", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("apple", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("surf", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("happy", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("think", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("whats", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("hold", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("Iaint", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("go", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("program", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("ihate", "AAAAAAAAAAAAAAAAAAAAAAAA", map);


  //not freeing any returned values in test for now
  char *key = "program";
  printf("Removed: %s, Got: %s\n", key, (char *)hashmap_remove(key, map));
  printf("Used after removal: %lu\n", map->used);
  
  test_value("program", "AAAAAAAAAAAAAAAAAAAAAAAA", map);

  key = "ihate";
  printf("Removed: %s, Got: %s\n", key, (char *)hashmap_remove(key, map));
  printf("Used after removal: %lu\n", map->used);
  
  test_value("ihate", "AAAAAAAAAAAAAAAAAAAAAAAA", map);

  key = "program";
  
  printf("Removed: %s, Got: %s\n", key, (char *)hashmap_remove(key, map));

  test_value("program", "BBBBBBBBBBBBBBBBBBBBBBBB", map);

  key = "hold";

  print_map(map);
  
  printf("Removed: %s, Got: %s\n", key, (char *)hashmap_remove(key, map));

  printf("%p\n", map->buckets[24]);

  print_map(map);
  test_value("hold", "CCCCCCCCCCCCCCCCCCCCCCCC", map);
  
  print_map(map);

  //SO MANY BUGS

  printf("CLEAR TEST\n");

  void **pointer_arr = hashmap_clear(map);
  //unsigned long arr_len =(sizeof(pointer_arr));
  //printf("%lu {", arr_len);
  printf("{");
  for(unsigned long i = 0; i < 10; i++) {
    printf("%lu: %s ", i, pointer_arr[i]);
  }
  printf("}\n");

  print_map(map);

  /*
  test_value("dogs", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("dogs", "BBBBBBBBBBBBBBBBBBBBBBBB", map);
  test_value("butter", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("woopie", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("strawberry", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("womps", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("eric", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("harold", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("mister", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("timothy", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("wegot", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("tony", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("kick", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("loof", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("apple", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("surf", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("happy", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("think", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("whats", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("hold", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("Iaint", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("go", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("program", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
  test_value("ihate", "AAAAAAAAAAAAAAAAAAAAAAAA", map);
*/
  print_map(map);

  printf("END\n");
  return 0;
}