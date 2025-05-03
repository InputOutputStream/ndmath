#include <ndmath/error.h>
#include <ndmath/helper.h>

// Function to handle axis error
void axis_error(char *axis)
{
    // Print error message for axis error
    fprintf(stderr, "AXIS ERROR\n");
    // Print details about the unknown axis causing the error
    fprintf(stderr, "UNKNOWN AXIS: %s\n", axis);
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}


// Function to handle shape error
void shape_error()
{
    // Print error message for shape error
    fprintf(stderr, "SHAPE ERROR\n");
    // Print details about why shape error occurred
    perror("Number of rows or columns cannot be zero\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle range error
void range_error(int max, int min)
{
    // Print error message for range error
    fprintf(stderr, "RANGE ERROR\n");
    // Print details about the range error
    fprintf(stderr, "MAXIMUM VALUE (%d) IS LESS THAN MINIMUM VALUE (%d)\n", max, min);
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle order error
void order_error(char *order)
{
    // Print error message for order error
    fprintf(stderr, "ORDER ERROR\n");
    // Print details about the ambiguous order causing the error
    fprintf(stderr, "AMBIGUOUS ORDER: %s\n", order);
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle dimension error during reshape
void dimension_error(ndarray_t *this, size_t new_cols, size_t new_rows)
{
    // Print error message for dimension error during reshape
    fprintf(stderr, "SHAPE ERROR\n");
    // Print details about the invalid dimensions for reshape operation
    fprintf(stderr, "INVALID DIMENSIONS: %ldx%ld AND %ldx%ld\n", this->shape[0], this->shape[1], new_cols, new_rows);
    // Clean up resources
    clean(this, NULL);
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle indexing error
void index_error()
{
    // Print error message for indexing error
    fprintf(stderr, "INDEXING ERROR\n");
    // Print details about why indexing error occurred
    fprintf(stderr, "INVALID INDICES PROVIDED\n");       
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle memory allocation error
void malloc_error()
{
    // Print error message for memory allocation error
    fprintf(stderr, "MEMORY ERROR\n");
    // Print details about why memory allocation failed
    perror("UNABLE TO ALLOCATE MEMORY\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle memory fault error
void memory_error(void)
{
    // Print error message for memory fault error
    fprintf(stderr, "MEMORY FAULT\n");
    // Print details about the cause of memory fault
    perror("SIZE OF POINTER EXCEEDS THE MAXIMUM ALLOWED SIZE\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}

// Function to handle null pointer error
void null_error()
{
    // Print error message for null pointer error
    fprintf(stderr, "NULL POINTER ERROR\n");
    // Print details about providing a null pointer
    perror("POINTER TO VOID PROVIDED\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}


// Function to handle matrix error
void mat_error()
{
    // Print error message for matrix error
    fprintf(stderr, "MATRIX ERROR\n");
    // Print details about why matrix error occurred
    perror("MATRIX IS NOT SQUARE\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}



// Function to handle division by zero error
void zero_error()
{
    // Print error message for division by zero error
    fprintf(stderr, "DIVISION BY ZERO ERROR\n");
    // Print details about why division by zero occurred
    perror("A DIVISION BY ZERO OCCURRED\n");
    // Exit the program with failure status
    exit(EXIT_FAILURE);
}
