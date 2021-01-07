#include "select.h"
#include "selection_sort.h"
#include "swap.h"
#include <stdlib.h>
#include <stdio.h>


unsigned int select_index(void *A, const unsigned int begin, 
                          const unsigned int end,
                          const size_t elem_size, 
                          total_order_type leq)
{
    
   
    const unsigned int n = end-begin +1; 
    if(n<=5)
    {   
        void *M = A+begin*elem_size; 
        selection_sort(M,n,elem_size,leq);
        return (begin+end) / 2; 
    }
      

     


   const unsigned int chunks = (n%5)? n/5 +1 : n/5;

   for(size_t i = 0; i <chunks; i++)
   {   
      

       
       unsigned int end2= 5*i+begin+4;
       unsigned int elem = 5; 
       if(i==chunks-1)
       {
           elem = n%5;
           end2 = end;
       }
       selection_sort(A+(5*i+begin)*elem_size,elem,elem_size,leq);
       swap(A +(begin+i)*elem_size,A+end*elem_size,elem_size);
   }

  
     return select_index(A,begin,begin +chunks,elem_size,leq);


}

void three_partition(void *A, unsigned int begin, unsigned int end,unsigned int pivot, const size_t elem_size, total_order_type leq, int* a)
{
   if(begin < pivot)
    {
        swap(A+begin*elem_size,A+pivot*elem_size,elem_size); 

    }

    int i = begin +1; 
    int j = begin +1; 
    int k = end; 

    while(i<=k)
    {
        if(!leq(A+i*elem_size,A+begin*elem_size))
        {
            swap(A+i*elem_size,A+k*elem_size,elem_size);
            k--;
        }
        else if((!leq(A+begin*elem_size,A+i*elem_size)))
        {
            i++;
        }
        else
        {
            swap(A+i*elem_size,A+j*elem_size,elem_size);
            i++;
            j++;
        }
        

    }

      for(int tras = 0; tras <= (j - begin - 1); tras++)
    {
        swap(A+(k - tras)*elem_size, A+(begin + tras)*elem_size, elem_size);
    }

    a[0] = k-(j-begin-1);

    a[1] = k;

    
}

void quick_select_aux(void *A, unsigned int begin, unsigned int end, const size_t elem_size, total_order_type leq)
{ 
    if(begin<end)
    { 
        int* a = (int*)malloc(sizeof(int)*2); 
        int p = select_index(A,begin,end,elem_size,leq);
        three_partition(A,begin,end,p,elem_size,leq,a);
        int first = a[0]; 
        int second = a[1]; 
        free(a);
        quick_select_aux(A,begin,first,elem_size,leq);
        quick_select_aux(A,second +1,end,elem_size,leq);
    }

}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order_type leq)
{
   quick_select_aux(A,0,n-1,elem_size,leq);
}