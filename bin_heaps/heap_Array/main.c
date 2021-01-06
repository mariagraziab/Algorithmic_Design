#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h" 
#include "orders.h" 
#include "utility.h"

#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec +	\
		   (double)ts.tv_nsec * 1e-9)

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}


int main() 
{  
//////FUNCTIONALITY TEST ////////
  heap h = INIT(intCmp, int const);

  int* a = (int*)malloc(sizeof(int)*10); 
  for(int i= 0; i<10; i++)
      a[i] = i; 
  a[2] = 139;
  a[1] = 20; 
  a[0] = 7; 
 int * b= malloc(sizeof(int));
  build_heap(a,10,&h);
  int* min_h = (int*)(min_value(&h));
  
  print_heap(&h, int_printer);

   min_h = (int*)(min_value(&h));
  printf("min is : %d\n",*min_h); 

  remove_min(&h); 
  printf("heap after removing the min:\n");
  print_heap(&h, int_printer);
   
 *b= 2;
  printf("Decrease the key of node 3 to %d\n",*b);
  decrease_key(&h,3,(void*)b); 
   print_heap(&h, int_printer);
  *b= 1;
   printf("Decrease the key of node 7 to %d\n",*b);
  decrease_key(&h,7,(void*)b); 
   print_heap(&h, int_printer);

  *b = 3; 
  insert_value(&h,b);
  printf("Insert value %d\n",*b);
   print_heap(&h, int_printer);
    *b= 7;
  decrease_key(&h,7,(void*)b); 
  print_heap(&h, int_printer);
   free(a); 
    delete_heap(&h); 
    
   
  ///PERFORMANCE TEST////////
 
  FILE *file1, *file2,*file3 ;
file1=fopen("BuildHeap.txt", "wt");
file2 =fopen("ExtractMin.txt","wt");
file3 =fopen("Decrease_key.txt","wt");

   struct timespec ts;
 double tstart, tstop, t2, t3; 
 double t_build, t_extract_min, t_decrease; 

  heap newHeap = INIT(intCmp, int const);

 
  
  for(size_t n = 1000; n<=100000; n+=1000)
  {   
     
    
     
      int *matrix = (int*)malloc(sizeof(int)*n);
     
      random_matrix(matrix,n);
      tstart = TCPU_TIME;
      build_heap(matrix,n,&newHeap); 
      build_heap(matrix,n,&newHeap); 
      build_heap(matrix,n,&newHeap); 
      build_heap(matrix,n,&newHeap); 
      t2 = TCPU_TIME;
      remove_min(&newHeap);
      remove_min(&newHeap);
      remove_min(&newHeap);
      remove_min(&newHeap);
      t3 = TCPU_TIME;
     *b= 1;
      decrease_key(&newHeap,n-5,(void*)b); 
      decrease_key(&newHeap,n-6,(void*)b); 
      decrease_key(&newHeap,n-7,(void*)b); 
      decrease_key(&newHeap,n-8,(void*)b); 
      tstop = TCPU_TIME;
      
      t_build = (t2-tstart)/4; 
      fprintf(file1,"%lu %g\n",n,t_build);

      t_extract_min= (t3-t2)/4; 
      fprintf(file2,"%lu %g\n",n,t_extract_min);

      t_decrease = (tstop -t3)/4; 
      fprintf(file3,"%lu %g\n",n,t_decrease);
  
      
      free(matrix);
     
     
  }

  delete_heap(&newHeap);


  fclose(file1); 
  fclose(file2); 
  fclose(file3); 




 

    return 0; 

}
