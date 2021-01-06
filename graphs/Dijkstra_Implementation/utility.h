#ifndef UTILITY_H__
#define UTILITY_H__
#include <stdlib.h> 

int** allocate_matrix(size_t n); 

int** allocate_zero_matrix(size_t n); 

void random_matrix(int** M,size_t n); 

void delete_matrix(int** M,size_t n); 

void random_sparse_matrix(int** M,size_t n); 

#endif 