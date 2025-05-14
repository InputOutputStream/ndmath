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

typedef struct ndarray
{
    size_t shape[3];  // 2-dimensional array
    double** data;     // Array of double values
    struct ndarray *next;
    size_t size;

} ndarray_t;


typedef struct ndarray_data_loader
{
    size_t lines;
    size_t rows;
    double **data;
}ndarray_data_loader;


/*

#define IDX(i,j,ncols) ((i)*(ncols)+(j))

a.data[IDX(i,j,a.shape[1])]

*/

typedef struct {
    const char* name;
    ndarray_t* array;
} named_array_t;


//RGB Pixel Value
typedef struct pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b; 
} pixel_t;

//Store Image matrix 
typedef struct image_matrix
{
    pixel_t **data;
    int width, height;
} image_matrix_t;


//BMP file Header
//#pragma push(push 2)
    typedef struct bmp_header
    {
        uint16_t signature; // BM for BMP ?
        uint32_t file_size; // Size of BMP file in bytes
        uint16_t reserved; // Reserved
        uint16_t reserved2; // Reserved
        uint16_t data_offset; // Offset to te image data
    }bmp_header_t;

    // Structure for BMP info header
    typedef struct bmp_info_header {
        uint32_t header_size;     // Size of this header in bytes
        int32_t  width;          // Width of the image
        int32_t  height;         // Height of the image
        uint16_t planes;         // Number of color planes
        uint16_t bits_per_pixel;   // Bits per pixel
        uint32_t compression;    // Compression method
        uint32_t image_size;      // Size of the image data
        int32_t  x_pixels_perM;    // Horizontal resolution
        int32_t  y_pixels_perM;    // Vertical resolution
        uint32_t colors_used;     // Number of colors in the color palette
        uint32_t colors_important;// Number of important colors
    } bmp_info_header_t;
//#pragma pack(pop)


typedef struct nd_image {
    ndarray_t *c1;
    ndarray_t *c2;
    ndarray_t *c3;
} nd_image_t;

typedef struct dim
{
    size_t cols;
    size_t rows;
}dim_t;

// Error handling struct
//To be implemented 
typedef enum {
    ND_SUCCESS,
    ND_SHAPE_ERROR,
    ND_INDEX_ERROR,
    ND_NULL_ERROR,
    ND_ALLOC_ERROR,
} nd_error_t;


#define TRACE() fprintf(stderr, "ERROR in function: %s\n", __func__)

#endif