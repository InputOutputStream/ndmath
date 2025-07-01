#include <ndmath/array.h>
#include <ndmath/error.h>
#include <ndmath/io.h>
#include <ndmath/helper.h>
#include <ndmath/operations.h>
#include <ndmath/conditionals.h>
#include <math.h>


    ndarray_t array(size_t rows, size_t cols)
    {

        if(rows == 0 || cols == 0)
        {
            shape_error();
        }
  
        ndarray_t arr = {0};
        arr.data = (double **)malloc(sizeof(double*) * rows);
        if(isnull(&arr))
        {
            malloc_error();
        }

        for(size_t i=0; i<rows; i++)
        {
            arr.data[i] = (double *)malloc(sizeof(double) * cols);    
            if(arr.data[i] == NULL)
            {
                malloc_error();
                clean(&arr, NULL);
            }
        }
        

        arr.shape[0] = rows;
        arr.shape[1] = cols;
        arr.size = arr.shape[0] * arr.shape[1]; 
        return arr;
    }


    ndarray_t zeros (size_t rows, size_t cols)
    {
        ndarray_t result = array(rows, cols);
        for(int i=0; i<(int)result.shape[0]; i++)
        {
            for(int j=0; j<(int)result.shape[1]; j++)
            {
                result.data[i][j] = 0;
            }
        }
        return result;
    }

    ndarray_t ones(size_t rows, size_t cols)
    {
        ndarray_t result = array(rows, cols);
        for(size_t i=0; i<result.shape[0]; i++)
        {
            for(size_t j=0; j<result.shape[1]; j++)
            {
                result.data[i][j] = 1;
            }
        }
        return result;
    }

    ndarray_t empty (size_t rows, size_t cols)
    {
        return array(rows, cols);
    }

    ndarray_t arange (int max, int min, size_t rows, size_t cols, char *order)
    {
        if(max < min)
        {
            range_error(max, min);
        }
        ndarray_t result = array(rows, cols);
        double spacing = ((double)(max - min)) / result.size;
        
        if(strcmp("asc", order)==0)
        {
            double token = (double)min;
            for(size_t i=0; i<result.shape[0]; i++)
            {
                for(size_t j=0; j<result.shape[1]; j++)
                {
                    result.data[i][j] = token;
                    token=token+spacing;
                }
            }
            return result;
        }
        else if(strcmp("dsc", order)==0)
        {
            double token = (double)max;

            for(size_t i=0; i<result.shape[0]; i++)
            {
                for(size_t j=0; j<result.shape[1]; j++)
                {
                    result.data[i][j] = token;
                    token=token-spacing;
                }
            }
            return result;
        }
        else
        {
            order_error(order);
            exit(1);
        }
    }
    
    ndarray_t linspace (int max, int min, double spacing,  size_t rows, size_t cols)
    {
        if(max < min)
        {
            range_error(max, min);
        }
                                 // TO DO
        double seed=(double)min; // CREATE A GENERAL SEED VAR FOR STUFFS
        
        ndarray_t result = array(rows, cols);
        for(size_t i=0; i<result.shape[0]; i++)
        {
            for(size_t j=0; j<result.shape[1]; j++)
            {
                result.data[i][j] = seed;
                seed+=spacing;
            }
        }
        return result;
    }

    ndarray_t argmin(ndarray_t *this, char *axis)
    {
        if(this == NULL)
        {
            null_error();
        }
        if(strcmp("x", axis)==0)  // Min along rows (for each row)
        {
            ndarray_t result = array(this->shape[0], 1);

            for(int i=0; i<(int)this->shape[0]; i++)
            {
                double temp = this->data[i][0];  // Initialize with first element of row
                for(int j=1; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] < temp)
                        temp = this->data[i][j];
                }
                result.data[i][0] = temp;
            }
            return result;
        }
        else if (strcmp("y", axis)==0)  // Min along columns (for each column)
        {
            ndarray_t result = array(1, this->shape[1]);

            for(int j=0; j<(int)this->shape[1]; j++)
            {
                double temp = this->data[0][j];  // Initialize with first element of column
                for(int i=1; i<(int)this->shape[0]; i++)
                {
                    if(this->data[i][j] < temp)
                        temp = this->data[i][j];
                }
                result.data[0][j] = temp;
            }
            return result;
        }
        else if (strcmp("all", axis)==0)
        {
            ndarray_t result = array(1, 1);
            result.data[0][0] = this->data[0][0];

            for(int i=0; i<(int)this->shape[0]; i++)
            {
                for(int j=0; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] < result.data[0][0])
                        result.data[0][0] = this->data[i][j];
                }
            }
            return result;
        }
        else
        { 
            axis_error(axis);
            exit(1);
        } 
    }

    ndarray_t argmax(ndarray_t *this, char *axis)
    {
        if(this == NULL)
        {
            null_error();
        }
        if(strcmp("x", axis)==0)  // Max along rows (for each row)
        {
            ndarray_t result = array(this->shape[0], 1);

            for(int i=0; i<(int)this->shape[0]; i++)
            {
                double temp = this->data[i][0];  // Initialize with first element of row
                for(int j=1; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] > temp)
                        temp = this->data[i][j];
                }
                result.data[i][0] = temp;
            }
            return result;
        }
        else if (strcmp("y", axis)==0)  // Max along columns (for each column)
        {
            ndarray_t result = array(1, this->shape[1]);

            for(int j=0; j<(int)this->shape[1]; j++)
            {
                double temp = this->data[0][j];  // Initialize with first element of column
                for(int i=1; i<(int)this->shape[0]; i++)
                {
                    if(this->data[i][j] > temp)
                        temp = this->data[i][j];
                }
                result.data[0][j] = temp;
            }
            return result;
        }
        else if (strcmp("all", axis)==0)
        {
            ndarray_t result = array(1, 1);
            result.data[0][0] = this->data[0][0];
            for(int i=0; i<(int)this->shape[0]; i++)
            {
                for(int j=0; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] > result.data[0][0])
                        result.data[0][0] = this->data[i][j];
                }
            }
            return result;
        }
        else
        { 
            axis_error(axis);
            exit(1);
        } 
    }



    ndarray_t lower_triangle(double fill, size_t rows, size_t cols)
    {
        ndarray_t result = zeros(rows, cols);  // Initialize with zeros
        for(int i = 0; i < (int)rows; i++)
        {
            for(int j = 0; j <= i && j < (int)cols; j++)  // j <= i for lower triangle
            {
                result.data[i][j] = fill;
            }
        }
        return result;
    }

    ndarray_t identity(size_t rows, size_t cols)
    {
        if(rows != cols)
        {
            mat_error();
        }

        ndarray_t result = zeros(rows, cols);  // Initialize with zeros
        for(size_t i = 0; i < rows; i++)
        {
            result.data[i][i] = 1;  // Set diagonal elements to 1
        }
        return result;
    }

    ndarray_t upper_triangle(double fill, size_t rows, size_t cols)
   {
        ndarray_t result = zeros(rows, cols);  // Initialize with zeros
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = i; j < cols; j++)  // j >= i for upper triangle
            {
                result.data[i][j] = fill;
            }
        }
        return result;
    }

    ndarray_t copy(ndarray_t *arrayB)
    {
        if(isnull(arrayB))
        {
            null_error();
            exit(EXIT_FAILURE);
        }

        ndarray_t result = array(arrayB->shape[0], arrayB->shape[1]);
        for(size_t i = 0; i<arrayB->shape[0]; i++)
        {
            for(size_t j = 0; j<arrayB->shape[1]; j++)
            {
                result.data[i][j] = arrayB->data[i][j];
            }
        }
        return result;
    }

    ndarray_t reshape(ndarray_t *this, size_t new_rows, size_t new_cols)
    {
        if(isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }
        
        if(new_cols*new_rows != this->size)
        {
            dimension_error(this, new_cols, new_rows);
        }
        
        ndarray_t result = array(new_rows, new_cols);

        size_t flat_idx = 0;
        for (size_t i = 0; i < new_rows; i++) {
            for (size_t j = 0; j < new_cols; j++) {
                size_t old_i = flat_idx / this->shape[1];
                size_t old_j = flat_idx % this->shape[1];
                result.data[i][j] = this->data[old_i][old_j];
                flat_idx++;
            }
        }


        return result;
    }
    void copy_block(double **dest, double **src, size_t start_i, size_t stop_i, size_t start_j, size_t stop_j) {
        for (size_t i = 0; i < stop_i - start_i; i++) {
            for (size_t j = 0; j < stop_j - start_j; j++) {
                dest[i][j] = src[start_i + i][start_j + j];
            }
        }
    }
    
    ndarray_t rslice(ndarray_t *this, size_t rows_start, size_t rows_stop) {
        if (isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }
        
    
        if (rows_start >= this->shape[0] || rows_stop > this->shape[0] || rows_start > rows_stop) {
            index_error();
        }
    
        size_t new_rows = rows_stop - rows_start;
        ndarray_t result = array(new_rows, this->shape[1]);
    
        copy_block(result.data, this->data, rows_start, rows_stop, 0, this->shape[1]);
    
        return result;
    }
    
    ndarray_t cslice(ndarray_t *this, size_t col_start, size_t col_stop) {
        
        if (isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }
        
    
        if (col_start >= this->shape[1] || col_stop > this->shape[1] || col_start > col_stop) {
            index_error();
        }
    
        ndarray_t temp = transpose(this);  // cols become rows
        size_t new_cols = col_stop - col_start;
    
        ndarray_t slice = array(new_cols, temp.shape[1]);
    
        copy_block(slice.data, temp.data, col_start, col_stop, 0, temp.shape[1]);
    
        clean(&temp, NULL);
        ndarray_t result = transpose(&slice);
        clean(&slice, NULL);
    
        return result;
    }
    


    void rassign_inplace(ndarray_t *this, ndarray_t *arrayB, size_t send_row_index, size_t rec_row_index)
    {
        if (isnull(this) || isnull(arrayB))
        {
            null_error();
            exit(EXIT_FAILURE);
        }

        if(this->shape[1] != arrayB->shape[1])
        {
            mat_error();
            exit(EXIT_FAILURE);
        }

        if(rec_row_index >= this->shape[0] || send_row_index >= arrayB->shape[0])
        {
            index_error();
            exit(EXIT_FAILURE);
        }

        for(size_t j = 0; j < this->shape[1]; j++)
        {
            this->data[rec_row_index][j] = arrayB->data[send_row_index][j];
        }
    }

    ndarray_t rassign(ndarray_t *this, ndarray_t *arrayB, size_t send_row_index, size_t rec_row_index)
    {
        ndarray_t result = copy(this);
        rassign_inplace(&result, arrayB, send_row_index, rec_row_index);
        return result;
    }

    ndarray_t cassign(ndarray_t *this, ndarray_t *arrayB, size_t send_col_index, size_t rec_col_index)
    {
        if (isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }
        
        if (isnull(arrayB))
        {
            null_error();
            exit(EXIT_FAILURE);
        }

        if(this->shape[0] != arrayB->shape[0])
        {
            mat_error();
        }

        ndarray_t result = copy(this);

        
        for(size_t i=0;i<result.shape[0];i++)
        {
            result.data[i][rec_col_index] = arrayB->data[i][send_col_index];
        }

        return result;
    }


    ndarray_t flatten(ndarray_t *this)
    {
        size_t rows = this->shape[0];
        size_t cols = this->shape[1];
        size_t total = rows * cols;
    
        ndarray_t result = array(1, total); // matrice ligne
        size_t index = 0;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result.data[0][index++] = this->data[i][j];
    
        return result;
    }

    ndarray_t deepcopy(ndarray_t *src) {
        ndarray_t dest = array(src->shape[0], src->shape[1]);
        for(size_t i = 0; i < src->shape[0]; ++i)
            for(size_t j = 0; j < src->shape[1]; ++j)
                dest.data[i][j] = src->data[i][j];
        return dest;
    }

    ndarray_t row_index(ndarray_t *this, int row)
    {   
        if(isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }

        if(row < 0 || row >= (int)this->shape[0])
        {
            index_error();
            exit(EXIT_FAILURE);
        }

        size_t cols = this->shape[1];
        ndarray_t dest = array(1, cols);
        
        for(size_t j = 0; j < cols; j++)
            dest.data[0][j] = this->data[row][j];  // Fixed: was dest.data[i][j]

        return dest;
    }   
    

    ndarray_t get_lines(ndarray_t *this, int *line_numbers, int number)
    {
        if(isnull(this))
        {
            null_error();
            exit(EXIT_FAILURE);
        }

        if(line_numbers == NULL)
        {
            fprintf(stderr, "Line Numbers is null\n");  // Fixed: was fprint
            exit(EXIT_FAILURE);
        }

        size_t cols = this->shape[1];
        ndarray_t result = array(number, cols);

        for(int i = 0; i < number; i++)
        {
            int line_idx = line_numbers[i];
            
            // Bounds checking
            if(line_idx < 0 || line_idx >= (int)this->shape[0])
            {
                fprintf(stderr, "Line index %d out of bounds\n", line_idx);
                clean(&result, NULL);
                exit(EXIT_FAILURE);
            }

            // Copy the specified line
            for(size_t j = 0; j < cols; j++)
            {
                result.data[i][j] = this->data[line_idx][j];
            }
        }

        return result;
    }


    static int compare_double_values(const void *a, const void *b) {
        const double *da = (const double *)a;
        const double *db = (const double *)b;
        
        if (*da < *db) return -1;
        if (*da > *db) return 1;
        return 0;
    }

    /**
     * @brief Check if two double values are approximately equal
     * @internal
     */
    static bool double_equals(double a, double b) {
        const double epsilon = 1e-9;
        return fabs(a - b) < epsilon;
    }

    // Improved get function with consistent error handling
    double get(ndarray_t *this, size_t row, size_t col)
    {
        if (this == NULL || this->data == NULL) {
            TRACE();
            fprintf(stderr, "NULL pointer passed to get()\n");
            exit(EXIT_FAILURE);
        }
        
        if (row >= this->shape[0] || col >= this->shape[1]) {
            TRACE();
            fprintf(stderr, "Index out of bounds: [%zu,%zu] for array shape [%zu,%zu]\n", 
                    row, col, this->shape[0], this->shape[1]);
            exit(EXIT_FAILURE);
        }
        
        return this->data[row][col];
    }

    // Improved set function with consistent error handling
    void set(ndarray_t *this, size_t row, size_t col, double value)
    {
        if (this == NULL || this->data == NULL) {
            TRACE();
            fprintf(stderr, "NULL pointer passed to set()\n");
            exit(EXIT_FAILURE);
        }
        
        if (row >= this->shape[0] || col >= this->shape[1]) {
            TRACE();
            fprintf(stderr, "Index out of bounds: [%zu,%zu] for array shape [%zu,%zu]\n", 
                    row, col, this->shape[0], this->shape[1]);
            exit(EXIT_FAILURE);
        }
        
        this->data[row][col] = value;
    }

    // Improved fill function with consistent error handling
    void fill(ndarray_t *this, double value)
    {
        if (this == NULL || this->data == NULL) {
            TRACE();
            fprintf(stderr, "NULL pointer passed to fill()\n");
            exit(EXIT_FAILURE);
        }
        
        for (size_t i = 0; i < this->shape[0]; i++) {
            for (size_t j = 0; j < this->shape[1]; j++) {
                this->data[i][j] = value;
            }
        }
    }

    // Improved describe function with better error handling and documentation
    ndarray_t describe(ndarray_t this, size_t idx) 
    {
        ndarray_t empty_result = {0};
        
        // Input validation
        if (this.data == NULL) {
            TRACE();
            fprintf(stderr, "NULL data pointer in describe()\n");
            return empty_result;
        }
        
        if (idx > 1) {
            TRACE();
            fprintf(stderr, "Invalid axis: %zu. Must be 0 (rows) or 1 (columns)\n", idx);
            return empty_result;
        }
        
        size_t total_elements = this.shape[0] * this.shape[1];
        if (total_elements == 0) {
            return empty_result;
        }
        
        // Collect all values
        double *all_values = malloc(total_elements * sizeof(double));
        if (all_values == NULL) {
            TRACE();
            fprintf(stderr, "Memory allocation failed for %zu elements\n", total_elements);
            return empty_result;
        }
        
        size_t value_idx = 0;
        for (size_t i = 0; i < this.shape[0]; i++) {
            for (size_t j = 0; j < this.shape[1]; j++) {
                all_values[value_idx++] = this.data[i][j];
            }
        }
        
        // Sort values
        qsort(all_values, total_elements, sizeof(double), compare_double_values);
        
        // Count unique values
        size_t unique_count = 1;
        for (size_t i = 1; i < total_elements; i++) {
            if (!double_equals(all_values[i], all_values[i-1])) {
                unique_count++;
            }
        }
        
        // Create result array
        ndarray_t result = {0};
       
        
        result.shape[0] = unique_count;
        result.shape[1] = 2; // [value, count]
        result.shape[2] = 0; // Not used for 2D
        result.size = unique_count * 2;
        result.next = NULL;
        
        // Allocate result data
        result.data = malloc(unique_count * sizeof(double*));
        if (result.data == NULL) {
            free(all_values);
            TRACE();
            fprintf(stderr, "Memory allocation failed for result data\n");
            return empty_result;
        }
        
        // Allocate each row
        for (size_t i = 0; i < unique_count; i++) {
            result.data[i] = malloc(2 * sizeof(double));
            if (result.data[i] == NULL) {
                // Cleanup previously allocated rows
                for (size_t j = 0; j < i; j++) {
                    free(result.data[j]);
                }
                free(result.data);
                    free(all_values);
                TRACE();
                fprintf(stderr, "Memory allocation failed for result row %zu\n", i);
                return empty_result;
            }
        }
        
        // Fill result with unique values and counts
        size_t result_idx = 0;
        size_t current_count = 1;
        double current_value = all_values[0];
        
        for (size_t i = 1; i < total_elements; i++) {
            if (double_equals(all_values[i], current_value)) {
                current_count++;
            } else {
                result.data[result_idx][0] = current_value;
                result.data[result_idx][1] = (double)current_count;
                result_idx++;
                
                current_value = all_values[i];
                current_count = 1;
            }
        }
        
        // Store the last value and count
        result.data[result_idx][0] = current_value;
        result.data[result_idx][1] = (double)current_count;
        
        free(all_values);
        return result;
    }

    // Improved count_rows function
    ndarray_t count_rows(ndarray_t this, double col_value, size_t col_index) 
    {
        ndarray_t empty_result = {0};
        
        // Input validation
        if (this.data == NULL) {
            TRACE();
            fprintf(stderr, "NULL data pointer in count_rows()\n");
            return empty_result;
        }
        
        if (col_index >= this.shape[1]) {
            TRACE();
            fprintf(stderr, "Column index %zu out of bounds for array with %zu columns\n", 
                    col_index, this.shape[1]);
            return empty_result;
        }
        
        // Create 1x1 result array
        ndarray_t result = {0};
        
        result.shape[0] = 1;
        result.shape[1] = 1;
        result.shape[2] = 0;
        result.size = 1;
        result.next = NULL;
        
        result.data = malloc(1 * sizeof(double*));
        if (result.data == NULL) {
            TRACE();
            fprintf(stderr, "Memory allocation failed for result data\n");
            return empty_result;
        }
        
        result.data[0] = malloc(1 * sizeof(double));
        if (result.data[0] == NULL) {
            free(result.data);
            TRACE();
            fprintf(stderr, "Memory allocation failed for result data row\n");
            return empty_result;
        }
        
        // Count matching rows
        size_t count = 0;
        for (size_t i = 0; i < this.shape[0]; i++) {
            if (double_equals(this.data[i][col_index], col_value)) {
                count++;
            }
        }
        
        result.data[0][0] = (double)count;
        return result;
    }

    // Improved count_cols function
    ndarray_t count_cols(ndarray_t this, double row_value, size_t row_index) 
    {
        ndarray_t empty_result = {0};
        
        // Input validation
        if (this.data == NULL) {
            TRACE();
            fprintf(stderr, "NULL data pointer in count_cols()\n");
            return empty_result;
        }
        
        if (row_index >= this.shape[0]) {
            TRACE();
            fprintf(stderr, "Row index %zu out of bounds for array with %zu rows\n", 
                    row_index, this.shape[0]);
            return empty_result;
        }
        
        // Create 1x1 result array
        ndarray_t result = {0};
        
        result.shape[0] = 1;
        result.shape[1] = 1;
        result.shape[2] = 0;
        result.size = 1;
        result.next = NULL;
        
        result.data = malloc(1 * sizeof(double*));
        if (result.data == NULL) {
            TRACE();
            fprintf(stderr, "Memory allocation failed for result data\n");
            return empty_result;
        }
        
        result.data[0] = malloc(1 * sizeof(double));
        if (result.data[0] == NULL) {
            free(result.data);
            TRACE();
            fprintf(stderr, "Memory allocation failed for result data row\n");
            return empty_result;
        }
        
        // Count matching columns in the specified row
        size_t count = 0;
        for (size_t j = 0; j < this.shape[1]; j++) {
            if (double_equals(this.data[row_index][j], row_value)) {
                count++;
            }
        }
        
        result.data[0][0] = (double)count;
        return result;
    }