#include <ndmath/conditionals.h>
#include <ndmath/error.h>

// Function to check if a matrix is square
bool issquare(ndarray_t *this)
{
    // Check if the matrix is square
    if(this->shape[0] != this->shape[1])
    {
        // Call mat_error function to handle the error
        return 1;
    }

    return 0;
}

bool is_zero_shape(ndarray_t *this)
{
    if(this->shape[0] == 0 || this->shape[1] == 0)
        return 1;
    return 0;
}

// Function to check if a pointer is null
bool isnull(ndarray_t *this)
{
    // Check if the pointer is null
    if(this->data == NULL || this == NULL)
    {
        // Call null_error function to handle the error
        return 1;
    }
    return 0;
}


    bool is_null_matrix_col(image_matrix_t *img, int i)
    {
       if (!img->data[i]) {
            fprintf(stderr, "Memory allocation failed for matrix data columns\n");
          return 1;
        }
        return 0;
    }

    bool is_null_matrix_row(image_matrix_t *img)
    {
        if (!img->data) {
        fprintf(stderr, "Memory allocation failed for matrix data rows\n");
            return 1;
        }
        return 0;
    }

    bool is_null_matrix(image_matrix_t *img)
    {
        if (!img) {
        fprintf(stderr, "Matrix is NULL\n");
            return 1;
        }
        return 0;
    }
