#ifndef __TEST__


double test(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t), 
	        float **C, float** A, float **B, size_t n);

double test2(void (*f)(float **, float **, float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t,size_t, size_t, size_t), 
	        float **C, float** AR, float **BR,float** A,float** B,
			  size_t n1, size_t nc, size_t n2, size_t nn);

double test3(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t,size_t,size_t), 
	        float **C, float** A, float **B, size_t n1, size_t nc,size_t n2);


#endif // __TEST__
