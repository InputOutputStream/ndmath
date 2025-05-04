#include <ndmath/conditionals.h>
#include <ndmath/error.h>

// Function to check if a matrix is square
void issquare(ndarray_t *this)
{
    // Check if the matrix is square
    if(this->shape[0] != this->shape[1])
    {
        // Call mat_error function to handle the error
        mat_error();
    }
}

// Function to check if a pointer is null
void isnull(ndarray_t *this)
{
    // Check if the pointer is null
    if(this->data == NULL || this == NULL)
    {
        // Call null_error function to handle the error
        null_error();
    }
}
