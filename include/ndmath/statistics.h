#ifndef STATISTICS
#define STATISTICS

    
    #include "ndarray.h"

    extern ndarray_t mean(ndarray_t *this, char *axis);
    extern ndarray_t std(ndarray_t *this, char *axis);
    extern ndarray_t variance(ndarray_t *this, char *axis);

#endif // !STATISTICS
