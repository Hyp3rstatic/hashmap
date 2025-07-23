#ifndef LIST_H
#define LIST_H

#include <stdlib.h> //for memory management

//list node - singly linked
//contains data and pointer to next
typedef struct node_sl {
  void *data;
  struct node_sl *next;
} node_sl;

//list - points to a head - end of the list is a node pointing to NULL
typedef node_sl *list_sl;

/* NODE FUNCTIONS */

//return a new list node containing data
node_sl *node_new(void *data);

/* LINKED LIST FUNCTIONS */

//return a new list
list_sl list_new(void);

//push - add an item to the end of a list
unsigned short list_push(void *data, list_sl list);

//remove - remove and item from the list by value
unsigned short list_remove(unsigned long idx, list_sl list);

#endif
