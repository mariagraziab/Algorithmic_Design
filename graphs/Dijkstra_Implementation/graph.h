#ifndef GRAPH_H__
#define GRAPH_H__

#include "node.h"
typedef struct Graph
{ 
  Node* nodes; 
  int size; 
  int** adj_matrix; 
  int infinity;

}Graph;

Graph* init_graph(int** matrix, int n); 

void delete_graph(Graph* g);

int get_size(Graph* g); 

void set_size(Graph* g, int numb); //in case we want to deal with a subset of the nodes

 const int find_infinity_value(int** matrix, int n); 

void init_nodes(Graph* G); 

void dijkstra_array(Graph* G, int src);

void dijkstra_heap(Graph* G, int src);

Node** build_queue(Graph* G);

Node* extract_min_new(Node** Q,int dim);

void relax(Node* u, Node* v, int w);

void print_dist(Graph* G, int id);

#endif
