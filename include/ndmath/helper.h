#ifndef PROTO
#define PROTO


#include "ndarray.h"


extern void clean(ndarray_t* arr, ...);
extern void print_named_array(ndarray_t a, char *name, size_t dp);
extern  void print_array(ndarray_t a, size_t dp);
extern  void free_array(ndarray_t *this);

extern  void clean_all_arrays(named_array_t* arrays, size_t count);
extern  void print_all_arrays(named_array_t* arrays, size_t count);

#endif