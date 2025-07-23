#ifndef NODE_SL_H
#define NODE_SL_H

#include "kv_pair.h" //for key-value pair data structure

//list node - singly linked
//contains data and pointer to next
typedef struct node_sl {
  kv_pair *data;
  struct node_sl *next;
} node_sl;

/* NODE FUNCTIONS */

//return a new list node containing data
node_sl *node_new(kv_pair *data);

#endif
