/**
 * @file trig.h
 * @brief Trigonometric functions for ndarray structures
 * 
 * This header file provides a comprehensive set of trigonometric functions that operate
 * element-wise on ndarray_t structures. All functions create new arrays with the same
 * dimensions as the input, containing the trigonometric transformation of each element.
 * These functions are similar to NumPy's trigonometric ufuncs.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 * 
 * @note All trigonometric functions assume input values are in radians
 * @note Functions return new ndarray_t structures - original arrays are not modified
 * @warning Input arrays should be validated (non-null, valid dimensions) before use
 */

#ifndef TRIG
#define TRIG

#include "ndarray.h"

/* ========================================================================== */
/*                         BASIC TRIGONOMETRIC FUNCTIONS                     */
/* ========================================================================== */

/**
 * @brief Computes the sine of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing sine values of each element
 * @note Input values are expected to be in radians
 * @note Output range: [-1, 1]
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array with values 0, π/4, π/2, π
 * ndarray_t angles = linspace(0, M_PI, M_PI/4, 1, 4);
 * ndarray_t sines = nd_sin(&angles);
 * // Result: [0, 0.707..., 1, 0]
 * @endcode
 */
extern ndarray_t nd_sin(ndarray_t *this);

/**
 * @brief Computes the cosine of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing cosine values of each element
 * @note Input values are expected to be in radians
 * @note Output range: [-1, 1]
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array with values 0, π/4, π/2, π
 * ndarray_t angles = linspace(0, M_PI, M_PI/4, 1, 4);
 * ndarray_t cosines = nd_cos(&angles);
 * // Result: [1, 0.707..., 0, -1]
 * @endcode
 */
extern ndarray_t nd_cos(ndarray_t *this);

/**
 * @brief Computes the tangent of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing tangent values of each element
 * @note Input values are expected to be in radians
 * @note Output range: (-∞, +∞)
 * @warning Produces undefined/infinite results at odd multiples of π/2 (π/2, 3π/2, etc.)
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array with values 0, π/4, π/3
 * ndarray_t angles = array(1, 3);
 * set(&angles, 0, 0, 0);
 * set(&angles, 0, 1, M_PI/4);
 * set(&angles, 0, 2, M_PI/3);
 * ndarray_t tangents = nd_tan(&angles);
 * // Result: [0, 1, 1.732...]
 * @endcode
 */
extern ndarray_t nd_tan(ndarray_t *this);

/* ========================================================================== */
/*                        HYPERBOLIC TRIGONOMETRIC FUNCTIONS                 */
/* ========================================================================== */

/**
 * @brief Computes the hyperbolic cosine of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing hyperbolic cosine values of each element
 * @note Formula: cosh(x) = (e^x + e^(-x)) / 2
 * @note Output range: [1, +∞)
 * @note Always positive for real inputs
 * @warning May overflow for very large input values
 * 
 * @code
 * ndarray_t values = linspace(-2, 2, 0.5, 1, 9);
 * ndarray_t cosh_values = nd_cosh(&values);
 * // Symmetric function: cosh(-x) = cosh(x)
 * @endcode
 */
extern ndarray_t nd_cosh(ndarray_t *this);

/**
 * @brief Computes the hyperbolic sine of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing hyperbolic sine values of each element
 * @note Formula: sinh(x) = (e^x - e^(-x)) / 2
 * @note Output range: (-∞, +∞)
 * @note Odd function: sinh(-x) = -sinh(x)
 * @warning May overflow for very large absolute input values
 * 
 * @code
 * ndarray_t values = linspace(-2, 2, 0.5, 1, 9);
 * ndarray_t sinh_values = nd_sinh(&values);
 * // Antisymmetric function: sinh(-x) = -sinh(x)
 * @endcode
 */
extern ndarray_t nd_sinh(ndarray_t *this);

/**
 * @brief Computes the hyperbolic tangent of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing hyperbolic tangent values of each element
 * @note Formula: tanh(x) = sinh(x) / cosh(x) = (e^(2x) - 1) / (e^(2x) + 1)
 * @note Output range: (-1, 1)
 * @note Commonly used as activation function in neural networks
 * @note Odd function: tanh(-x) = -tanh(x)
 * 
 * @code
 * ndarray_t values = linspace(-3, 3, 0.5, 1, 13);
 * ndarray_t tanh_values = nd_tanh(&values);
 * // Sigmoid-like curve, bounded between -1 and 1
 * @endcode
 */
extern ndarray_t nd_tanh(ndarray_t *this);

/* ========================================================================== */
/*                        RECIPROCAL TRIGONOMETRIC FUNCTIONS                 */
/* ========================================================================== */

/**
 * @brief Computes the cotangent of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing cotangent values of each element
 * @note Formula: cot(x) = cos(x) / sin(x) = 1 / tan(x)
 * @note Input values are expected to be in radians
 * @note Output range: (-∞, +∞)
 * @warning Produces undefined/infinite results at multiples of π (0, π, 2π, etc.)
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array avoiding multiples of π
 * ndarray_t angles = array(1, 3);
 * set(&angles, 0, 0, M_PI/4);   // 45°
 * set(&angles, 0, 1, M_PI/3);   // 60°
 * set(&angles, 0, 2, M_PI/6);   // 30°
 * ndarray_t cotangents = nd_cot(&angles);
 * // Result: [1, 0.577..., 1.732...]
 * @endcode
 */
extern ndarray_t nd_cot(ndarray_t *this);

/**
 * @brief Computes the secant of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing secant values of each element
 * @note Formula: sec(x) = 1 / cos(x)
 * @note Input values are expected to be in radians
 * @note Output range: (-∞, -1] ∪ [1, +∞)
 * @warning Produces undefined/infinite results at odd multiples of π/2 (π/2, 3π/2, etc.)
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array avoiding odd multiples of π/2
 * ndarray_t angles = array(1, 3);
 * set(&angles, 0, 0, 0);        // 0°
 * set(&angles, 0, 1, M_PI/4);   // 45°
 * set(&angles, 0, 2, M_PI/3);   // 60°
 * ndarray_t secants = nd_sec(&angles);
 * // Result: [1, 1.414..., 2]
 * @endcode
 */
extern ndarray_t nd_sec(ndarray_t *this);

/**
 * @brief Computes the cosecant of each element in an ndarray
 * @param this Pointer to the input ndarray
 * @return ndarray_t containing cosecant values of each element
 * @note Formula: cosec(x) = csc(x) = 1 / sin(x)
 * @note Input values are expected to be in radians
 * @note Output range: (-∞, -1] ∪ [1, +∞)
 * @warning Produces undefined/infinite results at multiples of π (0, π, 2π, etc.)
 * @warning Returns invalid result if input array is null or has invalid dimensions
 * 
 * @code
 * // Create array avoiding multiples of π
 * ndarray_t angles = array(1, 3);
 * set(&angles, 0, 0, M_PI/6);   // 30°
 * set(&angles, 0, 1, M_PI/4);   // 45°
 * set(&angles, 0, 2, M_PI/2);   // 90°
 * ndarray_t cosecants = nd_cosec(&angles);
 * // Result: [2, 1.414..., 1]
 * @endcode
 */
extern ndarray_t nd_cosec(ndarray_t *this);

#endif