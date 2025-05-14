
#include <ndmath/all.h>
#include <ndmath/image.h>


// Example usage
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    printf("Converting %s to matrix...\n", filename);
    
    image_matrix_t* matrix = image_to_matrix(filename);
    nd_image_t *im = matrix_to_ndarray(matrix);

    print_named_array(*im->c1, "The red channel", 2);
    
    if (matrix) {
        print_matrix_info(matrix);
        free_image_matrix(matrix);
        printf("Conversion completed successfully.\n");
    } else {
        printf("Conversion failed. Make sure libjpeg and libpng are properly installed.\n");
    }
    
    return 0;
}