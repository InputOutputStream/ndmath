/**
 * @file statistics.h
 * @brief Statistical functions for ndarray structures
 * 
 * This header file provides essential statistical functions that operate on ndarray_t
 * structures. Functions can compute statistics along specific axes (rows, columns)
 * or across the entire array (flattened). The implementation follows NumPy's
 * statistical function conventions for axis handling and output dimensions.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 * 
 * @note All functions support axis-wise computation and return new ndarray_t structures
 * @note Input arrays are not modified - original data remains unchanged
 * @warning Ensure input arrays are valid and non-empty before calling these functions
 */

#ifndef STATISTICS
#define STATISTICS

#include "ndarray.h"

/* ========================================================================== */
/*                           STATISTICAL FUNCTIONS                           */
/* ========================================================================== */

/**
 * @brief Computes the arithmetic mean of array elements along specified axis
 * @param this Pointer to the input ndarray
 * @param axis String specifying the computation axis:
 *             - "rows" or "0": Compute mean along rows (column-wise means)
 *             - "cols" or "1": Compute mean along columns (row-wise means)  
 *             - NULL or "None": Compute mean of entire flattened array
 * @return ndarray_t containing computed means
 * 
 * **Return Dimensions:**
 * - axis="rows": Returns (1, cols) array with mean of each column
 * - axis="cols": Returns (rows, 1) array with mean of each row
 * - axis=NULL: Returns (1, 1) array with overall mean
 * 
 * @note Formula: mean = (sum of all elements) / (number of elements)
 * @warning Returns invalid result if input array is null or has zero elements
 * @warning Division by zero will occur for empty arrays
 * 
 * @code
 * // Example: 3x3 array
 * ndarray_t data = array(3, 3);
 * // Fill with values: [[1,2,3], [4,5,6], [7,8,9]]
 * for(int i=0; i<3; i++) {
 *     for(int j=0; j<3; j++) {
 *         set(&data, i, j, i*3 + j + 1);
 *     }
 * }
 * 
 * ndarray_t col_means = mean(&data, "rows");    // [4, 5, 6] (1x3)
 * ndarray_t row_means = mean(&data, "cols");    // [2, 5, 8] (3x1)  
 * ndarray_t overall = mean(&data, NULL);        // [5] (1x1)
 * @endcode
 */
extern ndarray_t mean(ndarray_t *this, char *axis);

/**
 * @brief Computes the standard deviation of array elements along specified axis
 * @param this Pointer to the input ndarray
 * @param axis String specifying the computation axis:
 *             - "rows" or "0": Compute std along rows (column-wise standard deviations)
 *             - "cols" or "1": Compute std along columns (row-wise standard deviations)
 *             - NULL or "None": Compute std of entire flattened array
 * @return ndarray_t containing computed standard deviations
 * 
 * **Return Dimensions:**
 * - axis="rows": Returns (1, cols) array with std of each column
 * - axis="cols": Returns (rows, 1) array with std of each row
 * - axis=NULL: Returns (1, 1) array with overall std
 * 
 * @note Formula: std = sqrt(variance) = sqrt(E[(X - μ)²])
 * @note Uses population standard deviation (N in denominator) by default
 * @note Standard deviation measures spread/dispersion of data around the mean
 * @warning Returns 0 for arrays with identical elements
 * @warning Returns invalid result if input array is null or has zero elements
 * 
 * @code
 * // Example: Data with different spreads
 * ndarray_t data = array(2, 4);
 * // Row 1: [1, 1, 1, 1] - no variation
 * // Row 2: [1, 2, 3, 4] - linear progression
 * set(&data, 0, 0, 1); set(&data, 0, 1, 1); 
 * set(&data, 0, 2, 1); set(&data, 0, 3, 1);
 * set(&data, 1, 0, 1); set(&data, 1, 1, 2);
 * set(&data, 1, 2, 3); set(&data, 1, 3, 4);
 * 
 * ndarray_t row_stds = std(&data, "cols");     // [0, 1.29] approx
 * ndarray_t col_stds = std(&data, "rows");     // [0, 0.5, 1, 1.5]
 * @endcode
 */
extern ndarray_t std(ndarray_t *this, char *axis);

/**
 * @brief Computes the variance of array elements along specified axis
 * @param this Pointer to the input ndarray
 * @param axis String specifying the computation axis:
 *             - "rows" or "0": Compute variance along rows (column-wise variances)
 *             - "cols" or "1": Compute variance along columns (row-wise variances)
 *             - NULL or "None": Compute variance of entire flattened array
 * @return ndarray_t containing computed variances
 * 
 * **Return Dimensions:**
 * - axis="rows": Returns (1, cols) array with variance of each column
 * - axis="cols": Returns (rows, 1) array with variance of each row
 * - axis=NULL: Returns (1, 1) array with overall variance
 * 
 * @note Formula: variance = E[(X - μ)²] = (Σ(xi - mean)²) / N
 * @note Uses population variance (N in denominator) by default
 * @note Variance measures average squared deviation from the mean
 * @note Relationship: std = sqrt(variance)
 * @warning Returns 0 for arrays with identical elements
 * @warning Returns invalid result if input array is null or has zero elements
 * 
 * @code
 * // Example: Computing variance for quality control
 * ndarray_t measurements = array(1, 5);
 * // Measurement data: [98.2, 99.1, 100.0, 100.8, 101.9]
 * set(&measurements, 0, 0, 98.2);  set(&measurements, 0, 1, 99.1);
 * set(&measurements, 0, 2, 100.0); set(&measurements, 0, 3, 100.8);
 * set(&measurements, 0, 4, 101.9);
 * 
 * ndarray_t var_result = variance(&measurements, NULL);
 * // Result shows measurement precision/consistency
 * double measurement_variance = get(&var_result, 0, 0);
 * 
 * // For process control: if variance > threshold, investigate
 * if (measurement_variance > 2.0) {
 *     printf("High variability detected - check equipment\n");
 * }
 * @endcode
 */
extern ndarray_t variance(ndarray_t *this, char *axis);

#endif // !STATISTICS