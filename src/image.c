
#include <ndmath/image.h>
#include <ndmath/ndarray.h>
#include <ndmath/array.h>

// Function to initialize an image_matrix_t
image_matrix_t* create_image_matrix_t(int width, int height) {
    image_matrix_t* matrix = (image_matrix_t*)malloc(sizeof(image_matrix_t));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for image_matrix_t\n");
        return NULL;
    }
    
    matrix->width = width;
    matrix->height = height;
    matrix->data = (pixel_t**)malloc(height * sizeof(pixel_t*));
    
    if (!matrix->data) {
        fprintf(stderr, "Memory allocation failed for matrix data rows\n");
        free(matrix);
        return NULL;
    }
    
    for (int i = 0; i < height; i++) {
        matrix->data[i] = (pixel_t*)malloc(width * sizeof(pixel_t));
        if (!matrix->data[i]) {
            fprintf(stderr, "Memory allocation failed for matrix data columns\n");
            
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
        
        // Initialize pixel_ts to black
        memset(matrix->data[i], 0, width * sizeof(pixel_t));
    }
    
    return matrix;
}

// Function to free an image_matrix_t
void free_image_matrix(image_matrix_t* matrix) {
    if (!matrix) return;
    
    if (matrix->data) {
        for (int i = 0; i < matrix->height; i++) {
            if (matrix->data[i]) {
                free(matrix->data[i]);
            }
        }
        free(matrix->data);
    }
    
    free(matrix);
}

// Function to print matrix information for debugging
void print_matrix_info(image_matrix_t* matrix) {
    if (!matrix) {
        printf("Matrix is NULL\n");
        return;
    }
    
    printf("Matrix dimensions: %d x %d\n", matrix->width, matrix->height);
    printf("Sample pixel_t values:\n");
    
    // Print first 5x5 pixel_ts or less if the image is smaller
    int print_rows = (matrix->height < 5) ? matrix->height : 5;
    int print_cols = (matrix->width < 5) ? matrix->width : 5;
    
    for (int i = 0; i < print_rows; i++) {
        for (int j = 0; j < print_cols; j++) {
            printf("(%3d,%3d,%3d) ", 
                   matrix->data[i][j].r, 
                   matrix->data[i][j].g, 
                   matrix->data[i][j].b);
        }
        printf("\n");
    }
}


nd_image_t *matrix_to_ndarray(image_matrix_t *matrix)
{
    if(!matrix)
    {
        TRACE();
        fprintf(stderr, "ERROR: image matrix is nulli in %s", __func__);
        exit(EXIT_FAILURE);
    }

    nd_image_t *img = (nd_image_t *)malloc(sizeof(nd_image_t));
    if(!img)
    {
        TRACE();
        fprintf(stderr, "ERROR: Could not allocate memory in %s", __func__);
        exit(EXIT_FAILURE);
    }
    
    size_t rows = matrix->width;
    size_t cols = matrix->height;

    img->c1 = NULL;
    img->c2 = NULL;
    img->c3 = NULL;
    
    *img->c1 = array(rows, cols);   
    *img->c2 = array(rows, cols);
    *img->c3 = array(rows, cols);

    
    for(size_t i = 0; i<rows; i++)
    {
        for(size_t j = 0; j<cols; j++)
        {
            img->c1->data[i][j] = matrix->data[i][j].r;
            img->c2->data[i][j] = matrix->data[i][j].g;
            img->c3->data[i][j] = matrix->data[i][j].b;
        }

    }

    return img;
}


// Function to convert BMP image to matrix
image_matrix_t* bmp_to_matrix(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return NULL;
    }
    
    bmp_header_t header;
    if (fread(&header, sizeof(bmp_header_t), 1, file) != 1) {
        fprintf(stderr, "Error reading BMP header\n");
        fclose(file);
        return NULL;
    }
    
    // Check if it's a valid BMP file
    if (header.signature != 0x4D42) { // 'BM' in little endian
        fprintf(stderr, "Not a valid BMP file\n");
        fclose(file);
        return NULL;
    }
    
    bmp_info_header_t info_header;
    if (fread(&info_header, sizeof(bmp_info_header_t), 1, file) != 1) {
        fprintf(stderr, "Error reading BMP info header\n");
        fclose(file);
        return NULL;
    }
    
    // Check if color depth is supported
    if (info_header.bits_per_pixel != 24) {
        fprintf(stderr, "Only 24-bit BMP files are supported\n");
        fclose(file);
        return NULL;
    }
    
    // Calculate row padding (each row must be a multiple of 4 bytes)
    int paddingSize = (4 - ((info_header.width * 3) % 4)) % 4;
    
    // Seek to the beginning of pixel_t data
    fseek(file, header.data_offset, SEEK_SET);
    
    // Create matrix
    image_matrix_t* matrix = create_image_matrix_t(info_header.width, info_header.height);
    if (!matrix) {
        fclose(file);
        return NULL;
    }
    
    // BMP files are stored bottom-to-top, so we need to read them in reverse
    for (int y = info_header.height - 1; y >= 0; y--) {
        for (int x = 0; x < info_header.width; x++) {
            // BMP stores pixel_ts as BGR, we convert to RGB
            uint8_t b, g, r;
            
            if (fread(&b, 1, 1, file) != 1 ||
                fread(&g, 1, 1, file) != 1 ||
                fread(&r, 1, 1, file) != 1) {
                fprintf(stderr, "Error reading pixel_t data\n");
                free_image_matrix(matrix);
                fclose(file);
                return NULL;
            }
            
            matrix->data[info_header.height - 1 - y][x].r = r;
            matrix->data[info_header.height - 1 - y][x].g = g;
            matrix->data[info_header.height - 1 - y][x].b = b;
        }
        
        // Skip padding bytes
        fseek(file, paddingSize, SEEK_CUR);
    }
    
    fclose(file);
    return matrix;
}

// Function to check file format based on extension
int get_image_format(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!ext) return -1;
    
    if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".BMP") == 0) {
        return 0; // BMP
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || 
               strcmp(ext, ".JPG") == 0 || strcmp(ext, ".JPEG") == 0) {
        return 1; // JPEG
    } else if (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0) {
        return 2; // PNG
    }
    
    return -1; // Unsupported format
}

// Function to convert JPEG image to matrix using libjpeg
image_matrix_t* jpeg_to_matrix(const char* filename) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE* file;
    JSAMPARRAY buffer;
    int row_stride;
    image_matrix_t* matrix = NULL;
    
    // Open the JPEG file
    if ((file = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Could not open JPEG file: %s\n", filename);
        return NULL;
    }
    
    // Initialize the JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    
    // Read JPEG header
    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        fprintf(stderr, "Error reading JPEG header\n");
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        return NULL;
    }
    
    // Start decompression
    jpeg_start_decompress(&cinfo);
    
    // Create the image matrix
    matrix = create_image_matrix_t(cinfo.output_width, cinfo.output_height);
    if (!matrix) {
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        return NULL;
    }
    
    // Allocate buffer for reading scanlines
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
    
    // Read scanlines one by one and fill the matrix
    int y = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        
        for (size_t x = 0; x < cinfo.output_width; x++) {
            if (cinfo.output_components == 3) {
                // RGB image
                matrix->data[y][x].r = buffer[0][x * 3];
                matrix->data[y][x].g = buffer[0][x * 3 + 1];
                matrix->data[y][x].b = buffer[0][x * 3 + 2];
            } else if (cinfo.output_components == 1) {
                // Grayscale image
                matrix->data[y][x].r = 
                matrix->data[y][x].g = 
                matrix->data[y][x].b = buffer[0][x];
            }
        }
        y++;
    }
    
    // Clean up
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);
    
    return matrix;
}

// Function to convert PNG image to matrix using libpng
image_matrix_t* png_to_matrix(const char* filename) {
    FILE* file;
    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 width, height;
    int bit_depth, color_type;
    //int number_of_passes;
    png_bytep* row_pointers;
    image_matrix_t* matrix = NULL;
    
    // Open file
    if ((file = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Could not open PNG file: %s\n", filename);
        return NULL;
    }
    
    // Initialize libpng structures
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "png_create_read_struct failed\n");
        fclose(file);
        return NULL;
    }
    
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "png_create_info_struct failed\n");
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(file);
        return NULL;
    }
    
    // Error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error during PNG file reading\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        return NULL;
    }
    
    // Initialize PNG I/O
    png_init_io(png_ptr, file);
    
    // Read PNG header
    png_read_info(png_ptr, info_ptr);
    
    // Get PNG info
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 NULL, NULL, NULL);
    
    // Set transformations to get RGB data
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    
    // Update info after transformations
    png_read_update_info(png_ptr, info_ptr);
    
    // Create matrix
    matrix = create_image_matrix_t(width, height);
    if (!matrix) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for row pointers
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (size_t y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    
    // Read image data
    png_read_image(png_ptr, row_pointers);
    
    // Convert to our matrix format
    for (size_t y = 0; y < height; y++) {
        png_byte* row = row_pointers[y];
        for (size_t x = 0; x < width; x++) {
            // Get RGB values, ignore alpha if present
            int pos = x * (png_get_channels(png_ptr, info_ptr));
            matrix->data[y][x].r = row[pos];
            matrix->data[y][x].g = row[pos + 1];
            matrix->data[y][x].b = row[pos + 2];
        }
    }
    
    // Clean up
    for (size_t y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);
    
    return matrix;
}

// Main function to convert an image to a matrix
image_matrix_t* image_to_matrix(const char* filename) {
    if (!filename) {
        fprintf(stderr, "Invalid filename\n");
        return NULL;
    }

    
    int format = get_image_format(filename);
    switch (format) {
        case 0:  // BMP
            return bmp_to_matrix(filename);
        case 1:  // JPEG
            return jpeg_to_matrix(filename);
        case 2:  // PNG
            return png_to_matrix(filename);
        default:
            fprintf(stderr, "Unsupported image format: %s\n", filename);
            return NULL;
    }
}



/*I want to write a function child will convert an image (jpeg, jpg, png,) into a kind of matrix in c from scratch

Edit
I'll help you write a C function that converts an image into a matrix representation from scratch. 
This is a common operation in image processing where each pixel's color values are stored in a matrix format.

Let's create a function that:

Reads an image file (JPEG, JPG, PNG)
Converts it into a matrix structure
Does this without relying on external image processing libraries
Here's a complete implementation:


Image to Matrix Converter
Code 
I've created a C implementation that reads bitmap (BMP) image files and converts them into a matrix structure. Let me explain the key components:

What This Code Does
Defines Data Structures:
Pixel: Represents an RGB pixel with red, green, and blue components
ImageMatrix: Stores the 2D matrix of pixels and image dimensions
BMPHeader and BMPInfoHeader: Handle the BMP file format specifications
Provides Core Functions:
createImageMatrix: Allocates memory for the matrix structure
bmpToMatrix: Reads a BMP file and converts it to our matrix format
imageToMatrix: The main function you'd call to convert an image
Includes Memory Management:
Properly allocates and frees memory to avoid leaks
Includes error handling for failed allocations or file operations
Limitations
The current implementation fully supports BMP files but has a placeholder for JPG/PNG. This is because:

BMP is relatively simple to decode (uncompressed raw data)
JPG and PNG use complex compression algorithms that would require substantial code to implement from scratch
To Support JPG/PNG
You'd need to either:

Implement the full JPEG/PNG decoders (extremely complex undertaking)
Use existing libraries like libjpeg or libpng (most practical approach)
How to Use This Code
c
// Example usage
ImageMatrix* matrix = imageToMatrix("your_image.bmp");
if (matrix) {
    // Access pixels with: matrix->data[y][x].r, matrix->data[y][x].g, matrix->data[y][x].b
    // ...
    freeImageMatrix(matrix);
}
Would you like me to:

Explain any specific part of this implementation in more detail?
Modify the implementation to better suit your needs?
Provide guidance on how to implement JPEG or PNG support using external libraries?




Ok it for a kind of library 

In

I will use libjpeg and libpng that straight forward with them

I will also have to include in the make file that fact that these to have to be installed if absent

Edit
That's a great approach! Using libjpeg and libpng will make your library much more capable and practical. Let me update the code to integrate those libraries and handle the different image formats properly.


Image to Matrix Converter
Code ∙ Version 6 

Makefile
Code 
Perfect! I've updated the code to integrate libjpeg and libpng, and also created a Makefile to handle the dependencies. Let me explain the key changes:

1. Enhanced Image Format Support
The updated code now properly supports:

BMP files (using the original implementation)
JPEG files (using libjpeg)
PNG files (using libpng)
2. Implementation Details
For JPEG files:

Uses the standard libjpeg workflow to decompress JPEG images
Handles both RGB and grayscale JPEG images
Properly manages memory with the JPEG library's memory manager
For PNG files:

Uses libpng to read and decode PNG files
Applies transformations to ensure consistent RGB output
Handles various color types and bit depths
Properly manages memory for row pointers
3. Makefile Features
I've also created a Makefile that:

Checks for required dependencies (libjpeg and libpng)
Provides helpful installation instructions if dependencies are missing
Includes targets for building, cleaning, and installing the library
Works on different systems (Debian/Ubuntu, Fedora/RHEL, macOS)
How to Use
Compile the library:
bash
make
Install (optional):
bash
sudo make install
Use in your code:
c
#include "image_to_matrix.h"

// Load any supported image format
ImageMatrix* matrix = imageToMatrix("image.jpg");

// Access pixel data
Pixel p = matrix->data[y][x];

// Clean up when done
freeImageMatrix(matrix);
Next Steps
To make this a proper library, you might want to:

Create a header file (image_to_matrix.h) with public function declarations
Consider adding a function to write matrices back to image files
Add error handling for corrupted files
Add support for images with alpha channels
Would you like me to implement any of these next steps or make any other adjustments to the code?



*/