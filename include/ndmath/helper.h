/**
 * @file HELPER.h
 * @brief Function HELPERtypes for ndarray operations and utilities
 * 
 * This header file contains function declarations for managing, cleaning,
 * printing, and freeing ndarray data structures. It provides both individual
 * array operations and batch operations for multiple arrays.
 */

#ifndef HELPER
#define HELPER

#include "ndarray.h"

/**
 * @brief Clean one or more ndarray structures
 * 
 * This function performs cleanup operations on the provided ndarray and any
 * additional arrays passed as variadic arguments. The exact cleanup behavior
 * depends on the implementation.
 * 
 * @param arr Pointer to the primary ndarray to clean
 * @param ... Additional ndarray pointers (variadic arguments)
 * 
 * @note The function expects a NULL-terminated list of ndarray pointers
 *       or uses some other termination mechanism defined in the implementation
 */
extern void clean(ndarray_t* arr, ...);

/**
 * @brief Print a named ndarray with specified decimal precision
 * 
 * Prints the contents of an ndarray along with its name, formatting
 * floating-point values with the specified number of decimal places.
 * 
 * @param a The ndarray to print (passed by value)
 * @param name Pointer to a null-terminated string containing the array name
 * @param dp Number of decimal places to display for floating-point values
 * 
 * @pre name must point to a valid null-terminated string
 * @pre dp should be a reasonable value (typically 0-15)
 */
extern void print_named_array(ndarray_t a, char *name, size_t dp);

/**
 * @brief Print an ndarray with specified decimal precision
 * 
 * Prints the contents of an ndarray, formatting floating-point values
 * with the specified number of decimal places.
 * 
 * @param a The ndarray to print (passed by value)
 * @param dp Number of decimal places to display for floating-point values
 * 
 * @pre dp should be a reasonable value (typically 0-15)
 */
extern void print_array(ndarray_t a, size_t dp);

/**
 * @brief Free memory allocated for an ndarray
 * 
 * Deallocates all memory associated with the ndarray structure,
 * including any dynamically allocated data arrays. Sets the pointer
 * to NULL after freeing to prevent dangling pointer issues.
 * 
 * @param this Pointer to pointer to the ndarray to free
 * 
 * @pre this must not be NULL
 * @pre *this should point to a properly initialized ndarray or be NULL
 * @post *this is set to NULL after successful deallocation
 * 
 * @note It is safe to call this function with *this == NULL
 */
extern void free_array(ndarray_t *this);

/**
 * @brief Clean all arrays in a named_array_t collection
 * 
 * Performs cleanup operations on all arrays contained within the
 * named_array_t structure. This is a batch operation for multiple arrays.
 * 
 * @param arrays Pointer to the named_array_t structure containing arrays to clean
 * @param count Number of arrays in the collection
 * 
 * @pre arrays must not be NULL
 * @pre count must accurately represent the number of valid arrays in the collection
 */
extern void clean_all_arrays(named_array_t* arrays, size_t count);

/**
 * @brief Print all arrays in a named_array_t collection
 * 
 * Prints all arrays contained within the named_array_t structure,
 * displaying each array with its associated name. This is a batch
 * operation for multiple arrays.
 * 
 * @param arrays Pointer to the named_array_t structure containing arrays to print
 * @param count Number of arrays in the collection
 * 
 * @pre arrays must not be NULL
 * @pre count must accurately represent the number of valid arrays in the collection
 */
extern void print_all_arrays(named_array_t* arrays, size_t count);

#endif /* HELPER */