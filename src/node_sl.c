#include "include/node_sl.h"

/* NODE FUNCTIONS */

//return a new node
node_sl *node_new(kv_pair *data) {
  //allocate new node memory
  node_sl *new_node = (node_sl *)malloc(sizeof(node_sl));

  //set data;
  new_node->data = data;

  //set next to NULL
  new_node->next = NULL;

  return new_node;
}
