#include <stdlib.h>
#include "total_orders.h"
int leq_float(const void *a, const void *b)
{
  return *((float*)a)<=*((float*)b);
  //typecast to float
}

int leq_int(const void *a, const void *b)
{
  return *((int*)a)<=*((int*)b);
}

int geq_int(const void *a, const void *b)
{
  return *((int*)a)>=*((int*)b);
}

int leq_node(const void *a, const void *b)
{ 
  Node* one = (Node*)a; 
  Node* two= (Node*)b; 
  int aa = one->distance; 
  int bb = two->distance; 
  return aa <= bb; 
  
}

