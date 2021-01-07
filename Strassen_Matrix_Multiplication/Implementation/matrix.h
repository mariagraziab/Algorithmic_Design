#ifndef __MATRIX__
#include <stdlib.h>

void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n);
void naive_matrix_rectangular_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n1, const size_t n, const size_t n2);
int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols);

float **allocate_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float **A, const size_t rows);

float **allocate_zero_matrix(const size_t rows, const size_t cols); 



float **allocate_random_matrix(const size_t rows, const size_t cols);



void rectangular_matrix_multiplication(float **C,float **AR, float **BR, float const *const *const A,
                                float const *const *const B,
                                const size_t n1, const size_t n, const size_t n2,const size_t nn) ;



#endif //__MATRIX__

