#ifndef __BIN_HEAP__
#define __BIN_HEAP__

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "total_orders.h"

typedef struct{

void *A; 

unsigned int* Pos;

unsigned int* Free_pos;

unsigned int num_of_elem; //active nodes 

unsigned int total_nodes;

unsigned int max_size; 

int place; 

size_t key_size; 

total_order_type leq; 

void* max_order_value;

}binheap_type;


binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem, 
                         const unsigned int max_size, 
                         const size_t key_size, 
                         total_order_type leq);



const void *find_the_max(void *A,
                         const unsigned int num_of_elem,
                         const size_t key_size,
                         total_order_type leq);




void heapify(binheap_type *H, unsigned int node);

void *extract_min(binheap_type *H);

void insert_value(binheap_type *H, const void *value);

int is_heap_empty(const binheap_type *H);

const void *min_value(const binheap_type *H);

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value));


void decrease_key(binheap_type *H, unsigned int node, const void *value);

void delete_heap(binheap_type* H);

#endif