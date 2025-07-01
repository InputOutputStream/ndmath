/**
 * @file ndarray.h
 * @brief N-dimensional array library with image processing capabilities
 * 
 * This header file defines data structures and types for handling n-dimensional
 * arrays, image processing, and BMP file operations. It provides a comprehensive
 * framework for numerical computing, matrix operations, and computer vision tasks.
 * 
 * The library supports:
 * - Multi-dimensional arrays with dynamic memory allocation
 * - Image representation and manipulation (RGB pixel data)
 * - BMP file format reading/writing
 * - Error handling and debugging utilities
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 */

#ifndef NDARRAY
#define NDARRAY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>

/* =================================================================== */
/*                        CORE DATA STRUCTURES                        */
/* =================================================================== */

/**
 * @brief N-dimensional array structure for numerical computing
 * 
 * The ndarray_t structure represents a multi-dimensional array with support
 * for up to 3 dimensions. It uses dynamic memory allocation for efficient
 * storage and includes linked list capabilities for array management.
 * 
 * @note Currently optimized for 2D operations (matrices)
 * @warning Always initialize all fields before use
 */
typedef struct ndarray
{
    size_t shape[3];           /**< Dimensions of the array [depth, rows, cols] */
    double** data;             /**< 2D array of double-precision floating point values */
    struct ndarray *next;      /**< Pointer to next ndarray in linked list (optional) */
    size_t size;              /**< Total number of elements in the array */
} ndarray_t;

/**
 * @brief Data loader structure for reading external data
 * 
 * Helper structure used for loading data from files or external sources
 * into ndarray format. Provides metadata about the loaded data dimensions.
 */
typedef struct ndarray_data_loader
{
    size_t lines;             /**< Number of lines/rows in the loaded data */
    size_t rows;              /**< Number of data rows (may differ from lines) */
    double **data;            /**< 2D array containing the loaded data */
} ndarray_data_loader;

/**
 * @brief Named array structure for associative storage
 * 
 * Provides a way to associate string names with ndarray objects,
 * useful for variable management and symbolic computation.
 */
typedef struct {
    const char* name;         /**< Null-terminated string identifier */
    ndarray_t* array;         /**< Pointer to the associated ndarray */
} named_array_t;

/**
 * @brief Dimension specification structure
 * 
 * Simple structure for specifying 2D dimensions in a more readable format.
 * Commonly used in function parameters and return values.
 */
typedef struct dim
{
    size_t cols;              /**< Number of columns */
    size_t rows;              /**< Number of rows */
} dim_t;

/* =================================================================== */
/*                       IMAGE PROCESSING STRUCTURES                  */
/* =================================================================== */

/**
 * @brief RGB pixel representation
 * 
 * Represents a single pixel with red, green, and blue color components.
 * Each component is an 8-bit unsigned integer (0-255 range).
 * 
 * @note Standard RGB color model with 24-bit color depth
 */
typedef struct pixel
{
    uint8_t r;                /**< Red component (0-255) */
    uint8_t g;                /**< Green component (0-255) */
    uint8_t b;                /**< Blue component (0-255) */
} pixel_t;

/**
 * @brief Image matrix structure for pixel data storage
 * 
 * Stores a 2D array of RGB pixels representing an image, along with
 * dimension information. Used for image processing operations.
 * 
 * @note Memory layout: data[height][width] where data[0][0] is top-left pixel
 */
typedef struct image_matrix
{
    pixel_t **data;           /**< 2D array of RGB pixels */
    int width;                /**< Image width in pixels */
    int height;               /**< Image height in pixels */
} image_matrix_t;

/**
 * @brief Multi-channel image representation using ndarrays
 * 
 * Represents a color image as three separate ndarray channels (RGB).
 * This format is useful for advanced image processing and computer vision
 * operations where channel separation is beneficial.
 * 
 * @note Each channel should have the same dimensions
 * @warning Ensure all channel pointers are valid before use
 */
typedef struct nd_image {
    ndarray_t *c1;            /**< First channel (typically Red) */
    ndarray_t *c2;            /**< Second channel (typically Green) */
    ndarray_t *c3;            /**< Third channel (typically Blue) */
} nd_image_t;

/* =================================================================== */
/*                          BMP FILE STRUCTURES                       */
/* =================================================================== */

/**
 * @brief BMP file header structure
 * 
 * Contains the main header information for BMP (Bitmap) files.
 * This structure maps directly to the BMP file format specification.
 * 
 * @note Structure packing may be needed for proper file I/O
 * @warning Endianness considerations apply when reading/writing files
 */
typedef struct bmp_header
{
    uint16_t signature;       /**< File signature, should be 'BM' (0x4D42) */
    uint32_t file_size;       /**< Total size of BMP file in bytes */
    uint16_t reserved;        /**< Reserved field, should be 0 */
    uint16_t reserved2;       /**< Reserved field, should be 0 */
    uint16_t data_offset;     /**< Offset from file start to pixel data */
} bmp_header_t;

/**
 * @brief BMP information header structure
 * 
 * Contains detailed information about the BMP image format, dimensions,
 * and compression settings. Part of the BMP file format specification.
 * 
 * @note This is the BITMAPINFOHEADER format (40 bytes)
 * @warning Some fields may have different meanings based on BMP version
 */
typedef struct bmp_info_header {
    uint32_t header_size;     /**< Size of this header in bytes (usually 40) */
    int32_t  width;          /**< Image width in pixels (signed) */
    int32_t  height;         /**< Image height in pixels (signed, negative = top-down) */
    uint16_t planes;         /**< Number of color planes (must be 1) */
    uint16_t bits_per_pixel; /**< Bits per pixel (1, 4, 8, 16, 24, or 32) */
    uint32_t compression;    /**< Compression method (0 = uncompressed) */
    uint32_t image_size;     /**< Size of image data in bytes (0 for uncompressed) */
    int32_t  x_pixels_perM;  /**< Horizontal resolution in pixels per meter */
    int32_t  y_pixels_perM;  /**< Vertical resolution in pixels per meter */
    uint32_t colors_used;    /**< Number of colors in color palette (0 = all) */
    uint32_t colors_important; /**< Number of important colors (0 = all) */
} bmp_info_header_t;

/* =================================================================== */
/*                         ERROR HANDLING                             */
/* =================================================================== */

/**
 * @brief Error code enumeration for ndarray operations
 * 
 * Defines standard error codes returned by ndarray library functions.
 * Used for consistent error reporting and handling throughout the library.
 * 
 * @note Functions should return these codes to indicate operation status
 */
typedef enum {
    ND_SUCCESS = 0,           /**< Operation completed successfully */
    ND_SHAPE_ERROR,           /**< Array shape/dimension mismatch error */
    ND_INDEX_ERROR,           /**< Array index out of bounds error */
    ND_NULL_ERROR,            /**< Null pointer passed to function */
    ND_ALLOC_ERROR,           /**< Memory allocation failure */
} nd_error_t;

/* =================================================================== */
/*                            UTILITY MACROS                          */
/* =================================================================== */

/**
 * @brief Debug trace macro for error reporting
 * 
 * Prints the name of the current function to stderr when an error occurs.
 * Useful for debugging and tracing execution flow during development.
 * 
 * Usage: Call TRACE() when an error condition is detected
 * 
 * @note Only prints function name, not detailed error information
 * @warning Should not be used in production code due to performance impact
 */
#define TRACE() fprintf(stderr, "ERROR in function: %s\n", __func__)

/* =================================================================== */
/*                        COMMENTED UTILITIES                         */
/* =================================================================== */

/**
 * @brief Index calculation macro (COMMENTED OUT)
 * 
 * When uncommented, this macro would provide efficient 2D to 1D index
 * conversion for flattened array access patterns.
 * 
 * Usage example (when uncommented):
 * @code
 * // Access element at row i, column j in a flattened array
 * double value = a.data[IDX(i, j, a.shape[1])];
 * @endcode
 * 
 * @param i Row index
 * @param j Column index  
 * @param ncols Number of columns in the array
 * @return Linear index for flattened array access
 * 
 * @note Currently commented out - uncomment to use
 */
/*
#define IDX(i,j,ncols) ((i)*(ncols)+(j))
*/

#endif /* NDARRAY */

/**
 * @section Usage Examples
 * 
 * @subsection basic_usage Basic NDArray Usage
 * @code
 * // Create and initialize an ndarray
 * ndarray_t matrix;
 * matrix.shape[0] = 1;    // depth
 * matrix.shape[1] = 3;    // rows  
 * matrix.shape[2] = 4;    // cols
 * matrix.size = 12;       // total elements
 * 
 * // Allocate memory for 2D array
 * matrix.data = malloc(matrix.shape[1] * sizeof(double*));
 * for(int i = 0; i < matrix.shape[1]; i++) {
 *     matrix.data[i] = malloc(matrix.shape[2] * sizeof(double));
 * }
 * @endcode
 * 
 * @subsection image_usage Image Processing Usage
 * @code
 * // Create RGB pixel
 * pixel_t red_pixel = {255, 0, 0};  // Pure red
 * 
 * // Create image matrix
 * image_matrix_t image;
 * image.width = 640;
 * image.height = 480;
 * // ... allocate and initialize image.data
 * @endcode
 * 
 * @subsection error_handling Error Handling
 * @code
 * nd_error_t result = some_ndarray_function(&array);
 * if (result != ND_SUCCESS) {
 *     TRACE();
 *     // Handle specific error type
 *     switch(result) {
 *         case ND_NULL_ERROR:
 *             printf("Null pointer error\n");
 *             break;
 *         case ND_SHAPE_ERROR:
 *             printf("Shape mismatch error\n");
 *             break;
 *         // ... handle other errors
 *     }
 * }
 * @endcode
 */