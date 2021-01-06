#include <time.h>

double test(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t), 
	        float **C, float** A, float **B, size_t n)
{
  struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 1;

  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++) {
    f(C, (float const *const *const)A,
      (float const *const *const)B, n);
  }

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
  
  return accum / rep;
}

double test2(void (*f)(float **, float **, float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t,size_t, size_t, size_t), 
	                  float **C, float** AR, float **BR,float** A,float** B,
			              size_t n1, size_t nc, size_t n2, size_t nn)
{
   struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 1;

  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++) {
    f(C,AR,BR, (float const *const *const)A,
      (float const *const *const)B, n1,nc,n2,nn);
  }

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
  
  return accum / rep;

}


double test3(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t,size_t,size_t), 
	        float **C, float** A, float **B, size_t n1, size_t nc, size_t n2)
{
  struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 1;

  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++) {
    f(C, (float const *const *const)A,
      (float const *const *const)B, n1,nc, n2);
  }

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
  
  return accum / rep;
}



