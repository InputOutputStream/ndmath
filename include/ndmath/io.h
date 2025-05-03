#ifndef IO
#define IO

    #include "ndarray.h"

    #define __MAX__LINE__LENGTH__ 10000
    #define __MAX__LINES__NUMBER__ 100


    extern ndarray_t load_ndarray(char *absolute_path);
    extern void save_ndarray(ndarray_t *this, char *absolute_path);

#endif