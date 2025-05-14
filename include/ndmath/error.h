#ifndef ERROR
#define ERROR

    #include "ndarray.h"

    extern void axis_error(char *axis);
    extern void mat_error();
    extern void zero_error();
    extern void memory_error(void);
    extern void null_error();
    extern void dimension_error(ndarray_t *this, size_t new_cols, size_t new_rows);
    extern void index_error();
    extern void shape_error();
    extern void range_error(int max, int min);
    extern void order_error(char *order);
    extern void malloc_error();
    extern void not_null_error();
    extern void row_col_error();
    extern void null_matrix_data_rows();

#endif // !ERROR
