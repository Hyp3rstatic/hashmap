#include "include/list.h"

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
