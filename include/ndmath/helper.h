#ifndef PROTO
#define PROTO


#include "ndarray.h"


void clean(ndarray_t* arr, ...);
void print_array(ndarray_t a, size_t dp);


void clean_all_arrays(named_array_t* arrays, size_t count);
void print_all_arrays(named_array_t* arrays, size_t count);

#endif