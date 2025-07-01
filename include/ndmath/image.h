#ifndef IMAGE
#define IMAGE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <jpeglib.h>
#include <png.h>
#include <ndmath/ndarray.h>

/**
 * @brief Creates and initializes a new image matrix structure
 * 
 * Allocates memory for an image_matrix_t structure and initializes it with
 * the specified dimensions. The pixel data buffer is allocated but not initialized.
 * 
 * @param width The width of the image in pixels (must be > 0)
 * @param height The height of the image in pixels (must be > 0)
 * @return Pointer to the newly created image_matrix_t structure, or NULL on failure
 * 
 * @note The caller is responsible for freeing the returned structure using free_image_matrix()
 * @see free_image_matrix()
 */
extern image_matrix_t* create_image_matrix(int width, int height);

/**
 * @brief Deallocates memory used by an image matrix structure
 * 
 * Frees all memory associated with the image matrix, including the pixel data
 * buffer and the structure itself. Safe to call with NULL pointer.
 * 
 * @param matrix Pointer to the image_matrix_t structure to free (can be NULL)
 * 
 * @note After calling this function, the matrix pointer becomes invalid
 * @see create_image_matrix()
 */
extern void free_image_matrix(image_matrix_t* matrix);

/**
 * @brief Prints debugging information about an image matrix
 * 
 * Outputs matrix properties such as dimensions, color channels, bit depth,
 * and memory usage to stdout. Useful for debugging and development.
 * 
 * @param matrix Pointer to the image_matrix_t structure to inspect (must not be NULL)
 * 
 * @note If matrix is NULL, prints an error message instead
 */
extern void print_matrix_info(image_matrix_t* matrix);

/**
 * @brief Converts a BMP image file to an image matrix
 * 
 * Reads a BMP (Bitmap) image file and converts it to an internal image_matrix_t
 * representation. Supports common BMP formats including 24-bit and 32-bit color.
 * 
 * @param filename Path to the BMP image file to read
 * @return Pointer to newly created image_matrix_t containing the image data,
 *         or NULL if the file cannot be read or is not a valid BMP
 * 
 * @note The returned matrix must be freed using free_image_matrix()
 * @see image_to_matrix() for automatic format detection
 */
extern image_matrix_t* bmp_to_matrix(const char* filename);

/**
 * @brief Determines the image format based on file extension
 * 
 * Analyzes the file extension to determine the image format type.
 * Used internally for format detection and routing to appropriate decoders.
 * 
 * @param filename Path to the image file (extension will be analyzed)
 * @return Integer constant representing the detected image format:
 *         - Returns format-specific constant for supported formats (BMP, JPEG, PNG)
 *         - Returns error code for unsupported or unrecognized formats
 * 
 * @note Case-insensitive extension matching (e.g., .JPG and .jpg both work)
 */
extern int get_image_format(const char* filename);

/**
 * @brief Converts a JPEG image file to an image matrix using libjpeg
 * 
 * Reads a JPEG image file and converts it to an internal image_matrix_t
 * representation. Handles various JPEG formats including grayscale and RGB.
 * Uses the libjpeg library for robust JPEG decoding.
 * 
 * @param filename Path to the JPEG image file to read
 * @return Pointer to newly created image_matrix_t containing the image data,
 *         or NULL if the file cannot be read or is not a valid JPEG
 * 
 * @note The returned matrix must be freed using free_image_matrix()
 * @note Requires libjpeg to be linked
 * @see image_to_matrix() for automatic format detection
 */
extern image_matrix_t* jpeg_to_matrix(const char* filename);

/**
 * @brief Converts a PNG image file to an image matrix using libpng
 * 
 * Reads a PNG image file and converts it to an internal image_matrix_t
 * representation. Supports various PNG formats including RGB, RGBA, grayscale,
 * and palette-based images. Uses libpng for robust PNG decoding.
 * 
 * @param filename Path to the PNG image file to read
 * @return Pointer to newly created image_matrix_t containing the image data,
 *         or NULL if the file cannot be read or is not a valid PNG
 * 
 * @note The returned matrix must be freed using free_image_matrix()
 * @note Requires libpng to be linked
 * @see image_to_matrix() for automatic format detection
 */
extern image_matrix_t* png_to_matrix(const char* filename);

/**
 * @brief Converts an image matrix to an n-dimensional array structure
 * 
 * Transforms an image_matrix_t structure into an nd_image_t (n-dimensional array)
 * format compatible with the ndmath library. This conversion enables mathematical
 * operations and advanced image processing using ndarray functions.
 * 
 * @param matrix Pointer to the source image_matrix_t structure (must not be NULL)
 * @return Pointer to newly created nd_image_t structure containing the converted data,
 *         or NULL on conversion failure
 * 
 * @note The returned nd_image_t must be freed using appropriate ndmath cleanup functions
 * @note The original matrix remains unchanged and valid
 * @see ndarray_to_matrix() for reverse conversion
 */
extern nd_image_t *matrix_to_ndarray(image_matrix_t *matrix);

/**
 * @brief Converts an n-dimensional array to an image matrix structure
 * 
 * Transforms an nd_image_t (n-dimensional array) structure back into an
 * image_matrix_t format. This enables conversion from mathematical operations
 * back to standard image representations for display or file output.
 * 
 * @param nd_image Pointer to the source nd_image_t structure with RGB channels
 * @return Pointer to newly created image_matrix_t structure,
 *         or NULL on conversion failure
 * 
 * @note The function signature should likely be: image_matrix_t* ndarray_to_matrix(nd_image_t* nd_image)
 * @note The returned image_matrix_t must be freed using free_image_matrix()
 * @note All three channels (c1, c2, c3) in the nd_image must have matching dimensions
 * @see matrix_to_ndarray() for forward conversion
 */
extern nd_image_t *ndarray_to_matrix(image_matrix_t *matrix);

/**
 * @brief Universal image file converter with automatic format detection
 * 
 * Main entry point for image loading. Automatically detects the image format
 * based on file extension and calls the appropriate format-specific decoder.
 * Supports BMP, JPEG, and PNG formats.
 * 
 * @param filename Path to the image file to convert
 * @return Pointer to newly created image_matrix_t containing the image data,
 *         or NULL if the file cannot be read or format is unsupported
 * 
 * @note The returned matrix must be freed using free_image_matrix()
 * @note This is the recommended function for loading images of unknown format
 * @see get_image_format(), bmp_to_matrix(), jpeg_to_matrix(), png_to_matrix()
 * 
 * @example
 * ```c
 * image_matrix_t* img = image_to_matrix("photo.jpg");
 * if (img != NULL) {
 *     // Process the image
 *     print_matrix_info(img);
 *     free_image_matrix(img);
 * }
 * ```
 */
extern image_matrix_t* image_to_matrix(const char* filename);

#endif // !IMAGE