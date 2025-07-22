#include "include/hashmap.h"

//NOTE: for the outlining an 2D array is used for the buckets
//after adding a linked list implementation an array of linked lists will be used instead
//this is because linked lists offer better performance when adding and removing from buckets

/* NODE FUNCTIONS */

//return a new node
node_sl *node_new(void *data) {
  //allocate new node memory
  node_sl *new_node = (node_sl *)malloc(sizeof(node_sl));

  //set data;
  new_node->data = data;

  //set next to NULL
  new_node->next = NULL;

  return new_node;
}

/* LIST FUNCTIONS */

//return a new list
list_sl list_new(void) {
  list_sl new_list = NULL;
  return new_list;
}

//push - add an item to the end of a list
//use: list_push((typecast *)data, list)
unsigned short list_push(void *data, list_sl list) {
  //empty list
  if (list == NULL) {
    //assign list head
    list = node_new(data);
    return 1;
  }

  //create a node for iterating through the list
  node_sl *itr = list;

  //search for the node with a NULL next to insert the new node
  for (;;) {
    //target found
    if (itr->next == NULL) {
      itr->next = node_new(data);
      return 1;
    }

    //target not found: go to next node
    itr = itr->next;
  }
}

//remove - remove and item from the list by value
//does nothing if idx exceeds list length
unsigned short list_remove(unsigned long idx, list_sl list) {

  if (list == NULL) {
    return 2; //err: empty list
  }

  //the var used to free any nodes
  node_sl *free_node = NULL;

  //removing head
  if (idx == 0) {
    free_node = list;
    list = list->next;
    free(free_node->data); //free data in node;
    free(free_node); //free node
    return 1; //success
  }

  node_sl *itr = list;

  //iterate through list to idx, break if there are no more nodes to go to
  //list is starting at first index 0, before the loop begins
  //the itr->next is what will be freed, starting 0->1
  //user can implement index by value
  for (int i = 1; i < idx; i++) {
    //check if there are any nodes to go to
    if(itr->next == NULL) {
      return 3; //err: node not in list
    }
    itr = itr->next;
  }

  //fail if target node does not exist
  if (itr->next == NULL) {
    return 3; //err: node not in list
  }
 
  free_node = itr->next;

  //unlink node to be removed
  itr->next = itr->next->next;

  free(free_node->data); //free data in node;
  free(free_node); //free node

  return 1; //success
}

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
  new_map->size = 16;
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
