#include "utility.h"


int** allocate_matrix(size_t n)
{
    int** M = (int**)malloc(sizeof(int*)*n);
    for(size_t i= 0; i<n; i++)
    {
        M[i] = (int*)malloc(sizeof(int)*n); 
    }
    return M;
}

int** allocate_zero_matrix(size_t n)
{
    int** M = (int**)malloc(sizeof(int*)*n);
    for(size_t i= 0; i<n; i++)
    {
        M[i] = (int*)calloc(n,sizeof(int)); 
    }
    return M;
}

void random_matrix(int** M, size_t n)
{  
    srand(n);
  for(size_t i= 0; i<n; i++)
{ 
    for(size_t j = 0; j<n; j++)
    {   
        M[i][j]= abs((rand()-RAND_MAX / 2)%n);
    }
}  
}

void random_sparse_matrix(int** M,size_t n)
{  
    double b; 
    int j;
   for(size_t i = 0; i<n;i++)
   {
       for(int k=0; k<3; k++)
       {

        srand(i*n*k); 
        b = (double)(RAND_MAX -rand())/(double)(RAND_MAX); 
        j = b*n; 
        M[i][j] = abs((rand()-RAND_MAX / 2)%n);
        

       }

   }
}





void delete_matrix(int** M,size_t n)
{
  for(size_t i= 0; i<n; i++)
  {
      free(M[i]);
  }  
  free(M);
}