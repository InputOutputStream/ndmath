/**
 * @file random.h
 * @brief Random number generation functions and utilities for ndarray structures
 * 
 * This header file provides a comprehensive random number generation system based on
 * a 64-bit Linear Congruential Generator (LCG) and high-level functions for creating
 * random ndarray structures. The implementation offers both low-level RNG control
 * and convenient array generation functions similar to NumPy's random module.
 * 
 * The LCG implementation uses well-tested parameters for good statistical properties
 * and reasonable period length, suitable for most scientific computing applications.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 * 
 * @note All random functions support seeding for reproducible results
 * @note LCG implementation provides good performance with reasonable statistical quality
 * @warning For cryptographic applications, use a cryptographically secure RNG instead
 */

#ifndef RANDOM
#define RANDOM

/* ========================================================================== */
/*                           LCG PARAMETERS AND CONSTANTS                    */
/* ========================================================================== */

/**
 * @brief Multiplier coefficient for the Linear Congruential Generator
 * @note Value: 6364136223846793005ULL - proven to have good statistical properties
 * @note This is a well-tested multiplier that provides long period and good distribution
 */
#define LCG_A 6364136223846793005ULL

/**
 * @brief Increment coefficient for the Linear Congruential Generator  
 * @note Value: 1ULL - simple increment that works well with the chosen multiplier
 */
#define LCG_C 1ULL

/**
 * @brief Modulus for the Linear Congruential Generator
 * @note Value: 2^63 - provides maximum period length for 64-bit arithmetic
 * @note Using power of 2 enables efficient modulo operation via bit masking
 */
#define LCG_M (1ULL << 63)

#include "ndarray.h"
#include <stdint.h>
#include <stddef.h>

/* ========================================================================== */
/*                           RANDOM GENERATOR STRUCTURE                      */
/* ========================================================================== */

/**
 * @brief Structure representing a 64-bit Linear Congruential Generator state
 * @note Maintains the internal state needed for reproducible random number generation
 * @note Thread-safe when each thread uses its own generator instance
 */
typedef struct {
    uint64_t seed; /**< Current internal state/seed of the generator */
} lcg64_t;

/* ========================================================================== */
/*                           LOW-LEVEL RNG FUNCTIONS                         */
/* ========================================================================== */

/**
 * @brief Initializes the LCG random number generator with a seed
 * @param gen Pointer to the LCG generator structure to initialize
 * @param seed Initial seed value for the generator
 * @note Same seed will always produce the same sequence of random numbers
 * @note Use different seeds for independent random sequences
 * @warning Generator must be seeded before first use
 * 
 * @code
 * lcg64_t rng;
 * lcg64_seed(&rng, 12345);  // Initialize with seed 12345
 * @endcode
 */
extern void lcg64_seed(lcg64_t *gen, uint64_t seed);

/**
 * @brief Generates the next raw 64-bit random number
 * @param gen Pointer to the initialized LCG generator
 * @return uint64_t raw random number in range [0, 2^63-1]
 * @note This is the core generation function - other functions build on this
 * @note Generator state is automatically updated for the next call
 * @warning Generator must be seeded before calling this function
 * 
 * @code
 * lcg64_t rng;
 * lcg64_seed(&rng, 42);
 * uint64_t raw_random = lcg64_next(&rng);
 * @endcode
 */
extern uint64_t lcg64_next(lcg64_t *gen);

/**
 * @brief Generates a uniform random number in the range [0, 1)
 * @param gen Pointer to the initialized LCG generator
 * @return double uniform random value in [0, 1)
 * @note Converts raw integer output to floating-point uniform distribution
 * @note Never returns exactly 1.0, always less than 1.0
 * @note Useful for probability calculations and uniform sampling
 * 
 * @code
 * lcg64_t rng;
 * lcg64_seed(&rng, 123);
 * double prob = lcg64_next_uniform(&rng);  // Result: 0.0 <= prob < 1.0
 * if (prob < 0.5) {
 *     printf("Heads!\n");
 * } else {
 *     printf("Tails!\n");
 * }
 * @endcode
 */
extern double lcg64_next_uniform(lcg64_t *gen);

/**
 * @brief Generates a random integer in the specified range [min, max]
 * @param gen Pointer to the initialized LCG generator
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @return int random integer in the range [min, max]
 * @note Both min and max are included in the possible output range
 * @note Uses uniform distribution - all values in range are equally likely
 * @warning Undefined behavior if min > max
 * 
 * @code
 * lcg64_t rng;
 * lcg64_seed(&rng, 456);
 * int dice_roll = lcg64_randint(&rng, 1, 6);     // Simulate dice: 1-6
 * int random_index = lcg64_randint(&rng, 0, 99); // Array index: 0-99
 * @endcode
 */
extern int lcg64_randint(lcg64_t *gen, int min, int max);

/* ========================================================================== */
/*                           HIGH-LEVEL NDARRAY FUNCTIONS                    */
/* ========================================================================== */

/**
 * @brief Creates an ndarray filled with random numbers from standard normal distribution
 * @param rows Number of rows in the output array
 * @param cols Number of columns in the output array  
 * @param random_state Seed value for reproducible results
 * @return ndarray_t filled with normally distributed random values (μ=0, σ=1)
 * @note Uses Box-Muller transform or similar method to generate normal distribution
 * @note Mean ≈ 0, Standard deviation ≈ 1
 * @note Similar to NumPy's np.random.randn()
 * 
 * @code
 * // Generate 100 samples from standard normal distribution
 * ndarray_t normal_data = randn(10, 10, 42);
 * 
 * // Useful for:
 * // - Monte Carlo simulations
 * // - Statistical sampling
 * // - Machine learning weight initialization
 * @endcode
 */
extern ndarray_t randn(size_t rows, size_t cols, size_t random_state);

/**
 * @brief Creates an ndarray filled with random integers from specified range
 * @param rows Number of rows in the output array
 * @param cols Number of columns in the output array
 * @param max Maximum value (exclusive)
 * @param min Minimum value (inclusive)  
 * @param random_state Seed value for reproducible results
 * @return ndarray_t filled with random integers in range [min, max)
 * @note Range is [min, max) - min included, max excluded
 * @note Uniform distribution - all integers equally likely
 * @note Similar to NumPy's np.random.randint()
 * 
 * @code
 * // Generate 5x5 array of random integers from 0 to 99
 * ndarray_t random_ints = randint(5, 5, 100, 0, 123);
 * 
 * // Generate binary array (0s and 1s)
 * ndarray_t binary = randint(3, 3, 2, 0, 456);
 * 
 * // Simulate dice rolls
 * ndarray_t dice = randint(2, 3, 7, 1, 789);  // Values 1-6
 * @endcode
 */
extern ndarray_t randint(size_t rows, size_t cols, int max, int min, size_t random_state);

/**
 * @brief Randomly shuffles the elements of an ndarray in-place
 * @param this Pointer to the array to shuffle
 * @param random_state Seed value for reproducible shuffling
 * @return ndarray_t reference to the shuffled array (same as input)
 * @note Modifies the original array - elements are rearranged randomly
 * @note Uses Fisher-Yates shuffle algorithm for uniform permutation
 * @note All possible permutations are equally likely
 * @warning Original array order is lost after shuffling
 * 
 * @code
 * // Create ordered array [1, 2, 3, 4, 5, 6]
 * ndarray_t deck = arange(7, 1, 2, 3, "C");
 * 
 * // Shuffle the deck
 * ndarray_t shuffled_deck = shuffle(&deck, 999);
 * // Now contains same elements in random order
 * 
 * // Useful for:
 * // - Randomizing datasets
 * // - Card shuffling simulations  
 * // - Creating random permutations
 * @endcode
 */
extern ndarray_t shuffle(ndarray_t *this, size_t random_state);

/**
 * @brief Generates a random permutation of integers from 0 to n-1
 * @param n Number of elements in the permutation (0 to n-1)
 * @param seed Seed value for reproducible results
 * @return ndarray_t containing a random permutation of [0, 1, 2, ..., n-1]
 * @note Creates a 1D array with shape (1, n)
 * @note Each integer from 0 to n-1 appears exactly once
 * @note All n! possible permutations are equally likely
 * @note Similar to NumPy's np.random.permutation()
 * 
 * @code
 * // Generate random permutation of indices 0-9
 * ndarray_t perm = randperm(10, 777);
 * // Result might be: [7, 2, 9, 0, 4, 1, 8, 3, 6, 5]
 * 
 * // Use for random sampling without replacement
 * ndarray_t sample_indices = randperm(100, 888);  
 * // First 20 elements give random sample of 20 indices
 * 
 * // Create random ordering for cross-validation
 * ndarray_t cv_order = randperm(dataset_size, 101);
 * @endcode
 */
extern ndarray_t randperm(size_t n, uint64_t seed);

#endif