#ifndef LINALG
#define LINALG

    #include <ndmath/ndarray.h>
   

    extern double det(ndarray_t *this);
    extern ndarray_t inv(ndarray_t *this);
    extern ndarray_t eig(ndarray_t *this, size_t nbiters);
    extern ndarray_t svd(ndarray_t *this);
    extern ndarray_t norm(ndarray_t *this, char *axis);
    extern ndarray_t dot(ndarray_t* a, ndarray_t* b); // dot product between column vectors
    extern ndarray_t matmul(ndarray_t *this, ndarray_t *arrayB); // Matrix product
    extern ndarray_t outer(ndarray_t* a, ndarray_t* b); // outer vector product 

    extern void qr(ndarray_t *this, ndarray_t *Q, ndarray_t *R);

#endif