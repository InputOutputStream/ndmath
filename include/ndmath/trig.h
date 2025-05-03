#ifndef TRIG
#define TRIG

#include "ndarray.h"


extern ndarray_t nd_sin(ndarray_t *);
extern ndarray_t nd_cos(ndarray_t *);
extern ndarray_t nd_tan(ndarray_t *);

extern ndarray_t nd_cosh(ndarray_t *);
extern ndarray_t nd_sinh(ndarray_t *);
extern ndarray_t nd_tanh(ndarray_t *);

extern ndarray_t nd_cot(ndarray_t *this);
extern ndarray_t nd_sec(ndarray_t *this);
extern ndarray_t nd_cosec(ndarray_t *this);

#endif