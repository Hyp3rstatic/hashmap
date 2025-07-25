#ifndef LIST_SL_H
#define LIST_SL_H

#include "node_sl.h" //for key-value pair data structure

//list_head - points to a head - end of list is a node pointing to NULL
typedef node_sl head_sl;

/* LINKED LIST FUNCTIONS */

//return a new list head
head_sl *list_new(void);

//push - add an item to the end of a list
unsigned short list_push(kv_pair *data, head_sl *list_head);

//remove - remove and item from the list by index
//list_head is a pointer to pointer so it can be set to null in the event the list is emptied
void *list_remove(unsigned long idx, head_sl **list_head);

#endif
