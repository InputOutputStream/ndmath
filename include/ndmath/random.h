#ifndef RANDOM
#define RANDOM

#include "ndarray.h"

// ndarray rand(size_t rows, size_t cols, int max, int min);
extern ndarray_t randn(size_t rows, size_t cols, size_t random_state);
extern ndarray_t randint(size_t rows, size_t cols, int max, int min, size_t random_state);
extern ndarray_t shuffle(ndarray_t *this, int random_state);
//ndarray choice(int m, int n);
// poissons
// permutation
//logistic
//laplace
//get_state
//geometric
//gamma
//exponential
//dirichlet
//chisquare
//rayleight
//standard_exponential

#endif