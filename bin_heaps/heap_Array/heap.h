#ifndef _HEAP_H 
#define _HEAP_H
#include <stddef.h>
#include <string.h>
#include "orders.h"



//macro for initializationn

#define INIT(comp, type){NULL, comp, 0, 0, sizeof(type) }    

typedef int (*comparator)(void const *, void const*); 

typedef struct
{
    void *data; 

    comparator comp; 

    size_t size; 

    size_t capacity; 

    size_t data_size; 

}heap;

int root(); 

int parent(int); 

int left_child(int);

int right_child(int); 

int is_root(int); 

void* min_value(heap *h);

void build_heap(void*,size_t,heap*); 

void swap_elements(heap *h, void *a, void *b);

int is_valid(heap* h, int i);

int is_leaf(heap* h, int i);

void heapify(heap* H, int i);

void double_dimension(heap* h);

void insert_value(heap* h, void* value);

void decrease_key(heap* h,size_t i, void *value);

void remove_min(heap* h);

void delete_heap(heap* h);

void print_heap(heap *h, 
                void (*key_printer)(const void *value));

#endif
