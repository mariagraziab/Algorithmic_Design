#include "select.h"
#include "selection_sort.h"
#include "swap.h"
#include <stdio.h>


int select_pivot(void *A,int begin, int end, size_t elem_size, total_order_type leq)
{    

    int n = begin -end; 
     if(n <=5)
     {   void *M = A+begin*elem_size; 
         selection_sort(M,n,elem_size,leq);
         return (begin -end) / 2;
     }
    
    int chunks = (n%5)? n/5 +1 : n/5; 

    for(int i= 0; i<chunks;i++)
    {
        void *M = A +(begin+5*i)*elem_size; 
        int numb = (i == chunks-1)?n%5:5;
        selection_sort(M,numb,elem_size,leq);
        swap(A+i*elem_size,M+(numb/2)*elem_size,elem_size);
    }
    return select_pivot(A,begin,chunks,elem_size,leq);

    
    
}

int* three_partition(void* A,int begin,int end,int pivot,size_t elem_size,total_order_type leq)
{
    int* rl = (int*)malloc(sizeof(int)*2);
    swap(A+begin*elem_size,A+pivot*elem_size,elem_size); 
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
        else if(!leq(A+begin*elem_size,A+i*elem_size))
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

    rl[0] = k-(j-begin-1); 
    rl[1] = k; 

    return rl; 
    
   
}

void quick_aux(void *A,int begin, int end, const size_t elem_size,total_order_type leq)
{
    int* rl ;
    while(begin < end)
    { 
        int pivot = select_pivot(A,begin,end,elem_size,leq);
        rl = three_partition(A,begin,end-1,pivot,elem_size,leq);
        int first = rl[0] ; 
        int second = rl[1]; 
        quick_aux(A,0,first,elem_size,leq);
        quick_aux(A,second,end,elem_size,leq);
  }   
  free(rl);
  

     



}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order_type leq)
{


   quick_sort_aux(A,0,n-1,elem_size,leq);
}
