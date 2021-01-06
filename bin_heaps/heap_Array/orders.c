#include "orders.h"
int intCmp(void const *a, void const *b)
{ 
    //return (va < vb);
return *((int*)a) <= *((int*)b);


}
