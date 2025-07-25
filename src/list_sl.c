#include "include/list_sl.h"

/* LIST FUNCTIONS */

//return a new list head
head_sl *list_new(void) {
  head_sl *new_list_head = NULL;
  return new_list_head;
}

//push - add an item to the end of a list
//use: list_push((typecast *)data, list)
unsigned short list_push(kv_pair *data, head_sl *list_head) {
  //empty list
  if (list_head == NULL) {
    //assign list head
    list_head = node_new(data);
    return 1;
  }

  //create a node for iterating through the list
  node_sl *itr = list_head;

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

#include <stdio.h> //debug
//remove - remove and item from the list by value
//does nothing if idx exceeds list length
//list_head is a pointer to pointer so it can be set to null in the event the list is emptied
void *list_remove(unsigned long idx, head_sl **list_head) {

  if (*list_head == NULL) {
    return NULL; //err: empty list
  }

  //the var used to free any nodes
  node_sl *free_node = NULL;

  //removing head
  if (idx == 0) {
    free_node = *list_head;
    *list_head = (*list_head)->next;

    //hashmap exclusives
    free(free_node->data->key); //free key;
    void *value = free_node->data->value; //value to return;

    free(free_node->data); //free data in node;
    free(free_node); //free node

    printf("LIST HEAD: %p\n", list_head); //debug
    printf("FREE NODE: %p\n", free_node); //debug
    return value; //success
  }

  node_sl *itr = *list_head;

  //iterate through list to idx, break if there are no more nodes to go to
  //list is starting at first index 0, before the loop begins
  //the itr->next is what will be freed, starting 0->1
  //user can implement index by value
  for (int i = 1; i < idx; i++) {
    //check if there are any nodes to go to
    if(itr->next == NULL) {
      return NULL; //err: node not in list
    }
    itr = itr->next;
  }

  //fail if target node does not exist
  if (itr->next == NULL) {
    return NULL; //err: node not in list
  }
 
  free_node = itr->next;

  //unlink node to be removed
  itr->next = itr->next->next;

  free(free_node->data->key); //free key;
  void *value = free_node->data->value; //value to return;

  free(free_node->data); //free data in node;
  free(free_node); //free node

  return value; //success
}
