#ifndef IMAGE
#define IMAGE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <jpeglib.h>
#include <png.h>
#include <ndmath/ndarray.h>

// Function to initialize an ImageMatrix
extern image_matrix_t* create_image_matrix(int width, int height);

// Function to free an ImageMatrix
extern void free_image_matrix(image_matrix_t* matrix);

// Function to print matrix information for debugging
extern void print_matrix_info(image_matrix_t* matrix);

// Function to convert BMP image to matrix
extern image_matrix_t* bmp_to_matrix(const char* filename);

// Function to check file format based on extension
extern int get_image_format(const char* filename);

// Function to convert JPEG image to matrix using libjpeg
extern image_matrix_t* jpeg_to_matrix(const char* filename);

// Function to convert PNG image to matrix using libpng
extern image_matrix_t* png_to_matrix(const char* filename);

// Function to convert from Image Matrix To Nd_array
extern nd_image_t *matrix_to_ndarray(image_matrix_t *matrix);

// Function to convert from Nd_array to matrix
extern nd_image_t *ndarray_to_matrix(image_matrix_t *matrix);


// Main function to convert an image to a matrix
extern image_matrix_t* image_to_matrix(const char* filename);

#endif // !IMAGE