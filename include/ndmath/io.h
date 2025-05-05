#ifndef IO
#define IO

    #include "ndarray.h"

    const size_t __MAX__LINE__LENGTH__ = 1000000000;
    const size_t __MAX__LINES__NUMBER__ = 100;


    extern ndarray_t load_ndarray(char *absolute_path, long batch_size);
    extern void save_ndarray(ndarray_t *this, char *absolute_path);

#endif