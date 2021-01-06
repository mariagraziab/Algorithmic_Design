#include <stdio.h>
#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {
  size_t n = 1<<12;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);

  float **AR = allocate_zero_matrix(n, n);
  float **BR = allocate_zero_matrix(n, n);
  float **C = allocate_zero_matrix(n, n);
  float **CN = allocate_zero_matrix(n, n);
  printf("n\tStrassen's Alg.\tNaive Alg.\tSame result\n");
   for (size_t j = 1; j <= n; j *= 2) {

    printf("%ld\t", j);
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, j));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j));
    fflush(stdout);
  
    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, j, j));
  }

  printf("\n TESTS ON RECTANGULAR MATRICES  (n is the dimension of the 0 filled square matrices)\n"); 
  printf("n\tStrass Alg. Rectangular\tNaive Alg. Rectangular\tSame Result\t product dimension\n");
  for (size_t j = 1; j < n; j *= 2) {
    srand(j);
    size_t  nn=j*2; 
    double r1 = (double)(RAND_MAX -rand())/(double)(RAND_MAX); 
    double r2 = (double)(RAND_MAX -rand())/(double)(RAND_MAX); 
    double r3 = (double)(RAND_MAX -rand())/(double)(RAND_MAX); 
    size_t n1 = j+r1*j; 
    size_t nc = j+r2*j; 
    size_t n2 = j+r3*j; 
    
    printf("%ld\t", nn);
    
    fflush(stdout);
    
    printf("\t%lf\t", test2(rectangular_matrix_multiplication, C, AR, BR, A, B, n1, nc, n2, nn));
    fflush(stdout);
   
     printf("\t%lf\t",test3(naive_matrix_rectangular_multiplication,CN,A,B,n1,nc,n2));
     fflush(stdout);
     printf("\t%d", same_matrix((float const *const *const)C, (float const *const *const)CN, n1, n2));
     printf("\t %lu  %lu\n ",n1,n2);
  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);
  deallocate_matrix(AR, n);
  deallocate_matrix(BR, n);
  deallocate_matrix(C, n);
  deallocate_matrix(CN, n);

  return 0;
}
