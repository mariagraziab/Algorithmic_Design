#include "node.h" 

void set_distance(Node* n, int d)
{ 
    n->distance = d;
}

void set_pred(Node* n, int p)
{ 
   n->pred = p; 
}
void set_id(Node* n, int i)
{ 
    n->id = i;
}

void init_node(Node* n, int id, int pred, int distance)
{
    n->id = id; 
    n->pred = pred; 
    n->distance = distance; 
}


