#ifndef OPERATIONS
#define OPERATIONS

    #include "ndarray.h"


    extern ndarray_t sum(ndarray_t *this, ndarray_t *arrayB);// element wise addition
    extern ndarray_t subtract(ndarray_t *this, ndarray_t *arrayB); // Matric element wise subtraction
    extern ndarray_t transpose(ndarray_t *this);//tranpose of a matrix 
    extern ndarray_t nd_log2(ndarray_t *this);
    extern ndarray_t neg(ndarray_t *this);
    extern ndarray_t power(ndarray_t *this, double exponent);
    extern ndarray_t nd_log(ndarray_t *this);
    extern ndarray_t nd_exp(ndarray_t *this);
    extern ndarray_t nd_abs(ndarray_t *this);
    extern ndarray_t square(ndarray_t *this);
    extern ndarray_t cube(ndarray_t *this);
    extern ndarray_t nd_sqrt(ndarray_t *this);

    //ndarray_t reshape(ndarray_t *this, int new_rows, int new_cols);
    extern ndarray_t ravel(ndarray_t *this);// return a 1d array with all the matrix elements
    extern ndarray_t scaler(ndarray_t *this, double sc, char op); // matrix multiplied bya a scalar
    extern ndarray_t divide(ndarray_t *this, ndarray_t *arrayB);//elemen wise division of matrices

#endif