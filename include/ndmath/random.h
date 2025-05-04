#ifndef RANDOM
#define RANDOM


#define LCG_A 6364136223846793005ULL
#define LCG_C 1ULL
#define LCG_M (1ULL << 63)


#include "ndarray.h"
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint64_t seed;
} lcg64_t;

extern void lcg64_seed(lcg64_t *gen, uint64_t seed);

extern uint64_t lcg64_next(lcg64_t *gen);

// Convert to [0, 1)
extern double lcg64_next_uniform(lcg64_t *gen);


// Convert to integer in range [min, max]
extern int lcg64_randint(lcg64_t *gen, int min, int max);



// ndarray rand(size_t rows, size_t cols, int max, int min);
extern ndarray_t randn(size_t rows, size_t cols, size_t random_state);
extern ndarray_t randint(size_t rows, size_t cols, int max, int min, size_t random_state);
extern ndarray_t shuffle(ndarray_t *this, size_t random_state);
ndarray_t randperm(size_t n, uint64_t seed);

#endif