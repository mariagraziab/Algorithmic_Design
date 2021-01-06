#ifndef NODE_H__
#define NODE_H__

#include <stdlib.h> 


typedef struct Node
{ 
    int id; 
    int pred; 
    int distance; 
}Node;

void set_distance(Node* n, int d);

void set_pred(Node* n, int p);

void set_id(Node* n, int i);

void init_node(Node* n, int id, int pred, int distance);

#endif