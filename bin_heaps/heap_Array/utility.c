#include "utility.h" 

void random_matrix(int* M, size_t n)
{   
    //srand(n);
    for(size_t i = 0; i<n; i++)
    {
          M[i]= abs((rand()-RAND_MAX / 2)%n); 
    }
 
}

