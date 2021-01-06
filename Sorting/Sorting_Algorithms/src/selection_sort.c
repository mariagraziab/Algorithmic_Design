#include "selection_sort.h"
#include "swap.h"
void selection_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order_type leq)
{
    for(int i=n-1;i>0;i--)
    {
        int maxj =0;
        for(int j = 1; j<=i; j++)
        {
            if(!leq(A+j*elem_size,A+maxj*elem_size))
              maxj = j;
        }
        swap(A+i*elem_size, A+maxj*elem_size,elem_size);
    }
}


