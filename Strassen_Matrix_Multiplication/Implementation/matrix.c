#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "strassen.h"

void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n) 
{
  for(size_t y= 0;y<n;y++)
  { 
    for(size_t x= 0;x<n; x++ )
    { 
      float value = 0.0; 
      {
        for(size_t z = 0; z<n; z++)
        {
          value += A[y][z]*B[z][x];
        }
        C[y][x]=value; 
      }
    }
  }
}

void naive_matrix_rectangular_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n1, const size_t n, const size_t n2) 
{
  for(size_t y= 0;y<n1;y++)
  { 
    for(size_t x= 0;x<n2; x++ )
    { 
      float value = 0.0; 
      {
        for(size_t z = 0; z<n; z++)
        {
          value += A[y][z]*B[z][x];
        }
        C[y][x]=value; 
      }
    }
  }
}

void rectangular_matrix_multiplication(float **C, float **AR, float **BR, float const *const *const A,
                                float const *const *const B,
                                const size_t n1,const size_t nc, const size_t n2, const size_t nn)
{ 
  
  for(size_t i = 0; i<n1; i++)
  {
      memcpy(AR[i],A[i],nc*sizeof(float));
  }
   for(size_t i = 0; i<nc; i++)
  {
      memcpy(BR[i],A[i],n2*sizeof(float));
  }

  strassen_matrix_multiplication(C, (float const *const *const)AR,
                                    (float const *const *const)BR,nn) ;


}




   

float **allocate_matrix(const size_t rows, const size_t cols) {
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)malloc(sizeof(float) * cols);
  }

  return M;
}

float **allocate_zero_matrix(const size_t rows, const size_t cols)
{
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)calloc(cols,sizeof(float));
  }

  return M;
}



int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (A[i][j] != B[i][j]) {
        return 0;
      }
    }
  }

  return 1;
}

void deallocate_matrix(float **A, const size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(A[i]);
  }

  free(A);
}

float **allocate_random_matrix(const size_t rows, const size_t cols) {
  
  float **A = allocate_matrix(rows, cols);
  
  srand(10);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      A[i][j] = (rand() - RAND_MAX / 2) % 5;
    }
  }

  return A;
}



