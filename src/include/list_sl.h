#ifndef LIST_SL_H
#define LIST_SL_H

#include "kv_pair.h" //for key-value pair data structure

//list node - singly linked
//contains data and pointer to next
typedef struct node_sl {
  kv_pair *data;
  struct node_sl *next;
} node_sl;

//list - points to a head - end of the list is a node pointing to NULL
typedef node_sl *list_sl;

/* NODE FUNCTIONS */

//return a new list node containing data
node_sl *node_new(kv_pair *data);

/* LINKED LIST FUNCTIONS */

//return a new list
list_sl list_new(void);

//push - add an item to the end of a list
unsigned short list_push(kv_pair *data, list_sl list);

//remove - remove and item from the list by value
unsigned short list_remove(unsigned long idx, list_sl list);

#endif
