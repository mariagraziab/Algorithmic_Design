#include "heap_sort.h"
#include "binheap.h"

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order_type leq)
{
    

    binheap_type *h =  build_heap(A, n,n,elem_size, geq_int);
    for(int i = 0; i<n; i++){
        extract_min(h);
        }
}
