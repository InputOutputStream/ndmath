#ifndef CONDITIONALS
#define CONDITIONALS

    
    #include "ndarray.h"

    extern bool issquare(ndarray_t *this);
    extern bool isnull(ndarray_t *this);
    extern bool is_zero_shape(ndarray_t *this);
    
    extern bool is_null_matrix_row(image_matrix_t *img);
    extern bool is_null_matrix_col(image_matrix_t *img, int i);
    extern bool is_null_matrix(image_matrix_t *img);

#endif // !CONDITIONALS
