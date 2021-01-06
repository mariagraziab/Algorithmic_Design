#ifndef __TOTAL_ORDERS__
#define __TOTAL_ORDERS__

typedef int (*total_order_type)(const void *a, const void *b);
//total_order_type is a new type but it's a pointer to a function
// because I have defined thi pointer to a function as a new type,
//then I can use it as a parameter in a function call
int leq_float(const void *a, const void *b);
int leq_int(const void *a, const void *b);
int geq_int(const void *a, const void *b);

#endif