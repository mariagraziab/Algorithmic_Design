#include "insertion_sort.h"
#include "swap.h"
void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order_type leq)
{


    for(int i=1; i<n; i++)
    {
        void* j= A+i*elem_size;
        while(j!=A && leq(j,j-elem_size))
        {
             swap(j - elem_size, j, elem_size);
             j -= elem_size;

        }
    }
}