/**
 * @file operations.h
 * @brief Mathematical operations library for ndarray data structures
 * 
 * This header file defines a comprehensive set of mathematical operations
 * for n-dimensional arrays (ndarray_t). It provides both element-wise
 * operations and matrix transformations commonly used in numerical computing
 * and linear algebra applications.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 */

#ifndef OPERATIONS
#define OPERATIONS

    #include "ndarray.h"

    /* =================================================================== */
    /*                       ARITHMETIC OPERATIONS                        */
    /* =================================================================== */

    /**
     * @brief Performs element-wise addition of two ndarrays
     * 
     * Adds corresponding elements of two ndarrays and returns a new ndarray
     * containing the result. Both input arrays must have compatible dimensions.
     * 
     * @param this Pointer to the first ndarray operand
     * @param arrayB Pointer to the second ndarray operand
     * @return ndarray_t New ndarray containing element-wise sum
     * 
     * @note Arrays must have the same dimensions for element-wise addition
     * @warning Function may return invalid ndarray on dimension mismatch
     */
    extern ndarray_t sum(ndarray_t *this, ndarray_t *arrayB);

    /**
     * @brief Performs element-wise subtraction of two ndarrays
     * 
     * Subtracts corresponding elements of arrayB from this array and returns
     * a new ndarray containing the result (this - arrayB).
     * 
     * @param this Pointer to the minuend ndarray
     * @param arrayB Pointer to the subtrahend ndarray
     * @return ndarray_t New ndarray containing element-wise difference
     * 
     * @note Arrays must have the same dimensions for element-wise subtraction
     */
    extern ndarray_t subtract(ndarray_t *this, ndarray_t *arrayB);

    /**
     * @brief Performs element-wise division of two ndarrays
     * 
     * Divides corresponding elements of this array by arrayB and returns
     * a new ndarray containing the result (this / arrayB).
     * 
     * @param this Pointer to the dividend ndarray
     * @param arrayB Pointer to the divisor ndarray
     * @return ndarray_t New ndarray containing element-wise quotient
     * 
     * @note Arrays must have the same dimensions for element-wise division
     * @warning Division by zero elements in arrayB will result in undefined behavior
     */
    extern ndarray_t divide(ndarray_t *this, ndarray_t *arrayB);

    /**
     * @brief Performs scalar operations on an ndarray
     * 
     * Applies a scalar operation to all elements of the ndarray based on
     * the specified operation character.
     * 
     * @param this Pointer to the input ndarray
     * @param sc Scalar value to apply
     * @param op Operation character:
     *           - '+' : Addition (this + sc)
     *           - '-' : Subtraction (this - sc)
     *           - '*' : Multiplication (this * sc)
     *           - '/' : Division (this / sc)
     * @return ndarray_t New ndarray with scalar operation applied
     * 
     * @warning Division by zero scalar will result in undefined behavior
     */
    extern ndarray_t scaler(ndarray_t *this, double sc, char op);

    /* =================================================================== */
    /*                      MATHEMATICAL FUNCTIONS                        */
    /* =================================================================== */

    /**
     * @brief Computes the natural logarithm of each element
     * 
     * Applies the natural logarithm function to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with ln(x) applied to each element
     * 
     * @warning Undefined behavior for non-positive elements
     */
    extern ndarray_t nd_log(ndarray_t *this);

    /**
     * @brief Computes the base-2 logarithm of each element
     * 
     * Applies the base-2 logarithm function to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with log2(x) applied to each element
     * 
     * @warning Undefined behavior for non-positive elements
     */
    extern ndarray_t nd_log2(ndarray_t *this);

    /**
     * @brief Computes the exponential function of each element
     * 
     * Applies e^x to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with exp(x) applied to each element
     */
    extern ndarray_t nd_exp(ndarray_t *this);

    /**
     * @brief Computes the absolute value of each element
     * 
     * Applies the absolute value function to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with |x| applied to each element
     */
    extern ndarray_t nd_abs(ndarray_t *this);

    /**
     * @brief Computes the square root of each element
     * 
     * Applies the square root function to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with sqrt(x) applied to each element
     * 
     * @warning Undefined behavior for negative elements
     */
    extern ndarray_t nd_sqrt(ndarray_t *this);

    /**
     * @brief Raises each element to a specified power
     * 
     * Computes x^exponent for each element x in the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @param exponent The power to raise each element to
     * @return ndarray_t New ndarray with power function applied
     */
    extern ndarray_t power(ndarray_t *this, double exponent);

    /**
     * @brief Computes the square of each element
     * 
     * Applies x^2 to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with x^2 applied to each element
     */
    extern ndarray_t square(ndarray_t *this);

    /**
     * @brief Computes the cube of each element
     * 
     * Applies x^3 to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with x^3 applied to each element
     */
    extern ndarray_t cube(ndarray_t *this);

    /**
     * @brief Negates each element of the ndarray
     * 
     * Applies unary negation (-x) to each element of the ndarray.
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New ndarray with negated elements
     */
    extern ndarray_t neg(ndarray_t *this);

    /* =================================================================== */
    /*                      MATRIX TRANSFORMATIONS                        */
    /* =================================================================== */

    /**
     * @brief Computes the transpose of a matrix
     * 
     * Returns the transpose of the input matrix, where rows become columns
     * and columns become rows. For a matrix A[i][j], the transpose A^T[j][i].
     * 
     * @param this Pointer to the input matrix ndarray
     * @return ndarray_t New ndarray containing the transposed matrix
     * 
     * @note For 1D arrays, returns a copy of the original array
     */
    extern ndarray_t transpose(ndarray_t *this);

    /**
     * @brief Flattens an ndarray into a 1D array
     * 
     * Returns a new 1D ndarray containing all elements of the input array
     * in row-major order (C-style ordering).
     * 
     * @param this Pointer to the input ndarray
     * @return ndarray_t New 1D ndarray with all elements flattened
     * 
     * @note The total number of elements remains unchanged
     */
    extern ndarray_t ravel(ndarray_t *this);

    /* =================================================================== */
    /*                         FUTURE FEATURES                            */
    /* =================================================================== */

    /**
     * @brief Reshape an ndarray to new dimensions (COMMENTED OUT)
     * 
     * This function is currently commented out in the implementation.
     * When implemented, it would reshape the ndarray to specified dimensions
     * while preserving the total number of elements.
     * 
     * @param this Pointer to the input ndarray
     * @param new_rows New number of rows
     * @param new_cols New number of columns
     * @return ndarray_t Reshaped ndarray
     * 
     * @note This function is not currently available
     */
    //ndarray_t reshape(ndarray_t *this, int new_rows, int new_cols);

#endif /* OPERATIONS */