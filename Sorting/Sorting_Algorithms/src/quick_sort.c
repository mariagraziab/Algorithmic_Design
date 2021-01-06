#include "quick_sort.h"
#include "swap.h"
#include <stdio.h>

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order_type leq)
{
    quick_sort_aux(A,0,n-1,elem_size,leq);
}

void quick_sort_aux(void *A,int begin, int end, const size_t elem_size,total_order_type leq)
{    
    
    while(begin<end)
    {   
        int p = partition(A,begin,end,begin,elem_size,leq);
        quick_sort_aux(A,begin,p-1,elem_size,leq);
        begin = p+1;
       
    }

}

int partition(void *A,int begin, int end, int pivot, size_t elem_size, total_order_type leq)
{   
    if(begin < pivot)
    {
        swap(A+begin*elem_size,A+pivot*elem_size,elem_size); 
    }

    leq(A+1*elem_size,A+0*elem_size);

     int piv = begin; 
     int i = piv +1; 
     int j = end; 
    
    while(i<=j)
    {  
        
        if(!leq(A+i*elem_size,A+piv*elem_size))
        {   
           
           swap(A+i*elem_size,A+j*elem_size,elem_size);   
          
         
           j = j-1;
          
        }
        else
        {
        
            i = i +1;
        }
       
    }
    
     swap(A+j*elem_size,A+piv*elem_size,elem_size); 

     return j;
}


