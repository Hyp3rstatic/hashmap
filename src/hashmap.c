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
  new_map->buckets = (head_sl **)malloc(sizeof(head_sl *) * new_map->size);

  //blank all buckets
  for(unsigned short i = 0; i < new_map->size; i++) {
    new_map->buckets[i] = NULL;
  }

  return new_map;
}

//insert a new key-value pair into a hashmap
//fails if key is already in use
//returns success status
//TODO: Finish Func
unsigned short hashmap_insert(char *key, void *value, hashmap *map) {
  //NULL checks
  if (map == NULL || key == NULL) {
    return 2; //err: NULL args
  }
  
  //check to make sure key is not in use
  node_sl *itr = NULL; //create itr for buckets

  //store strlen in var to save time in strncmps
  unsigned long key_len = strlen(key);
  
  //if key does not exist itr should eventually be null
  for(itr = map->buckets[fnv_1a(key)%map->size]; itr != NULL; itr = itr->next) {
    //key found
    if (strncmp(itr->data->key, key, key_len) == 0) {
      return 3; //err: key already in use
    }
  }

  //transfer all kv_pairs in the old map to the new map
    //go through every bucket, for every non null bucket:
      //for every entry, rehash key into new map, free the node
      //go to the next node (have it saved before free)
    //once all nodes are free, free the bucket
  //once all buckets are free, free the map
  //set map to the new map

  //check to see if resize is necessary
  //TODO: after resize, another resize may be necessary :(
  //turn resize into a function, then keep calling until ratio is satisfied
  if (hashmap_ratio(map) >= 0.75) {
    map->size = map->size * 2; // double capacity
     //create new buckets with doubled capcity
    head_sl **new_buckets = (head_sl **)malloc(sizeof(head_sl *) * map->size);
    
    //blank new buckets
    for(unsigned long i = 0; i < map->size; i++) {
      new_buckets[i] = NULL;
    }
    
    //ok to divide by 2 since the sizes are all multiple of 2
    //loop through all buckets
    for(unsigned long i = 0; i < map->size/2; i++) {
      if (map->buckets[i] == NULL) {
        continue;
      }

      for(itr = map->buckets[i]; itr != NULL;) {
        //hash into new buckets
        //assign head of bucket to search
        node_sl *itr_new_buckets = new_buckets[fnv_1a(itr->data->key)%map->size];

        //if the bucket is empty create a new bucket with a new_kv_pair taking the func args
        if (itr_new_buckets == NULL) {
          new_buckets[fnv_1a(itr->data->key)%map->size] = itr;
        }

        else {
          //if the bucket exists, append a new kv_pair as the last entry
          //loop to the end of the list
          for(; itr_new_buckets->next != NULL; itr_new_buckets = itr_new_buckets->next);

          //move entry
          itr_new_buckets->next = itr; 
        }
        
        node_sl *moved_node = itr;

        itr = itr->next;

        moved_node->next = NULL; //set next to NULL in new bucket
      }
    }
  
    //free buckets
    free(map->buckets);

    //set new buckets
    map->buckets = new_buckets;
  }

  //assign head of bucket to search
  itr = map->buckets[fnv_1a(key)%map->size];

  //if the bucket is empty create a new bucket with a new_kv_pair taking the func args
  if (itr == NULL) {
    map->buckets[fnv_1a(key)%map->size] = node_new(kv_pair_new(key, value));
    map->used += 1;
    return 1; //success
  }

  //if the bucket exists, append a new kv_pair as the last entry
  //loop to the end of the list
  for(; itr->next != NULL; itr = itr->next);

  //create new entry
  itr->next = node_new(kv_pair_new(key, value));

  return 1; //success
}

//remove a key-value pair from a hashmap by key
//return removed value: up to user to handle data mem management
//TODO: Finish Func
//use list remove
void *hashmap_remove(char *key, hashmap *map) {
  if (key == NULL || map == NULL) {
    return NULL; //err: null args
  }

  //assign itr to head of bucket being searched
  node_sl *itr = map->buckets[fnv_1a(key)%map->size];

  //jank but convenient 'for' conditions
  for(unsigned long i = 0, key_len = strlen(key); itr != NULL; itr = itr->next, i++) {
    if (strncmp(itr->data->key, key, key_len) == 0) {
      //if bucket is freed decrement capacity
      if(map->buckets[fnv_1a(key)%map->size]->next == NULL) {
        map->used -= 1;
      }
      return list_remove(i, &map->buckets[fnv_1a(key)%map->size]); //remove and free node/bucket
    }
  }
  
  return NULL; //err: pair does not exist
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
  node_sl *itr = map->buckets[idx];

  //store strlen in var to save time in strncmps
  unsigned long key_len = strlen(key);
  
  //NULL check
  if (itr == NULL) {
    return NULL; //err: pair does not exist
  }

  for(;;) {
    //key found
    if (strncmp(itr->data->key, key, key_len) == 0) {
      return itr->data->value;
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

#include <stdio.h> //debug
//remove all key-value pairs in a hashmap
//return success status
//TODO: Finish Func
//return should give back an array of all values for user to manage as they wish
void **hashmap_clear(hashmap *map) {
  if (map == NULL) {
    return NULL; //err: hashmap does not exist
  }

  //set used to 0
  map->used = 0;
  
  //array with all values
  void **value_arr = NULL;
  unsigned long value_arr_len = 0;

  for(unsigned long i = 0; i < map->size; i++) {
    
    while(map->buckets[i] != NULL) {
      value_arr = (void **)realloc(value_arr, value_arr_len++ * sizeof(void *));
      //printf("arrlen: %lu\n", value_arr_len); //debug
      //printf("key: %s\n", map->buckets[i]->data->key); //debug
      void *cleared_val = hashmap_remove(map->buckets[i]->data->key, map);

      //printf("returned value: %s\n", (char *)hashmap_remove(map->buckets[i]->data->key, map)); //debug
      
      //there is a problem in remove causing memory to be freed that shouldn't be //debug
      value_arr[value_arr_len-1] = cleared_val;
      printf("idx: %lu value: %s\n", value_arr_len, value_arr[value_arr_len-1]);
  //debug
  printf("{");
  for(unsigned long i = 0; i < value_arr_len; i++) {
    printf("%lu: %s ", i, value_arr[i]);
  }
  printf("}\n");
    }
  }

  //debug
  printf("{");
  for(unsigned long i = 0; i < value_arr_len; i++) {
    printf("%lu: %s ", i, value_arr[i]);
  }
  printf("}\n");

  return value_arr; //success
}

//return the ratio of buckets used to hashmap size
//for resizing checks
float hashmap_ratio(hashmap *map) {
  return ((float)map->used/(float)map->size);
}

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

int main(int argc, char *argv[]) {
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
