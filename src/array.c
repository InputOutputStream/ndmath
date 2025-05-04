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
        if(arr.data == NULL)
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
        if(strcmp("x", axis)==0)
        {
            ndarray_t result = array(this->shape[0], 1);
            double temp=this->data[0][0];

            for(int i=0; i<(int)this->shape[0]; i++)
            {
                for(int j=1; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] < temp)
                            temp = this->data[i][j];
                }
                result.data[i][0] = temp;
                
                if(i+1 < (int)this->shape[0])
                    temp = this->data[i+1][0];
            }
            return result;
        }
        else if (strcmp("y", axis)==0)
        {
            ndarray_t result = array(1, this->shape[1]);
            double temp=this->data[0][0];

            for(int i=0; i<(int)this->shape[1]; i++)
            {
                for(int j=1; j<(int)this->shape[0]; j++)
                {
                     if(this->data[j][i] < temp)
                            temp = this->data[j][i];
                }
                result.data[0][i] = temp;
               
                if(i+1 < (int)this->shape[1])
                    temp = this->data[0][i+1];
            }
            return result;
        }
        else if (strcmp("all", axis)==0)
        {
            ndarray_t result = array(1, 1);
            result.data[0][0] = this->data[0][0];

            for(int i=1; i<(int)this->shape[0]; i++)
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
        if(strcmp("x", axis)==0)
        {
            ndarray_t result = array(this->shape[0], 1);
            double temp=this->data[0][0];

            for(int i=0; i<(int)this->shape[0]; i++)
            {
                for(int j=1; j<(int)this->shape[1]; j++)
                {
                    if(this->data[i][j] > temp)
                            temp = this->data[i][j];
                }
                result.data[i][0] = temp;
                
                if(i+1 < (int)this->shape[0])
                    temp = this->data[i+1][0];
            }
            return result;
        }
        else if (strcmp("y", axis)==0)
        {
            ndarray_t result =array(1, this->shape[1]);
            double temp=this->data[0][0];

            for(int i=0; i<(int)this->shape[1]; i++)
            {
                for(int j=1; j<(int)this->shape[0]; j++)
                {
                     if(this->data[j][i] > temp)
                            temp = this->data[j][i];
                }
                result.data[0][i] = temp;
               
                if(i+1 < (int)this->shape[1])
                    temp = this->data[0][i+1];
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
        
        ndarray_t result = array(rows, cols);
        for(int i=rows-1;i>=0;i--)
        {
            for(int j=i; j>=0; j--)
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

        ndarray_t result = array(rows, cols);
        for(size_t i=0 ;i<rows;i++)
        {
            for(size_t j=i; j<cols; j++)
            {
                if(i==j)
                    result.data[i][j] = 1;
            }
        }
        
        return result;
    }

    ndarray_t upper_triangle(double fill, size_t rows, size_t cols)
    {
        ndarray_t result = array(rows, cols);
        for(size_t i=0;i<rows;i++)
        {
            for(size_t j=i; j<cols; j++)
            {
                result.data[i][j] = fill;
            }
        }
        
        return result;
    }

    ndarray_t copy(ndarray_t *arrayB)
    {
        if(arrayB == NULL)
        {
            null_error();
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
        isnull(this);
        
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
        isnull(this);
    
        if (rows_start >= this->shape[0] || rows_stop > this->shape[0] || rows_start > rows_stop) {
            index_error();
        }
    
        size_t new_rows = rows_stop - rows_start;
        ndarray_t result = array(new_rows, this->shape[1]);
    
        copy_block(result.data, this->data, rows_start, rows_stop, 0, this->shape[1]);
    
        return result;
    }
    
    ndarray_t cslice(ndarray_t *this, size_t col_start, size_t col_stop) {
        isnull(this);
    
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
    


    ndarray_t rassign(ndarray_t *this, ndarray_t *arrayB, size_t send_row_index, size_t rec_row_index)
    {
        isnull(this);
        isnull(arrayB);

        if(this->shape[1] != arrayB ->shape[1])
        {
            mat_error();
        }

        ndarray_t result = copy(this);

        for(size_t j=0; j<this->shape[1]; j++)
        {

            result.data[rec_row_index][j] = arrayB->data[send_row_index][j];
        }
        
        return result;
    }

    ndarray_t cassign(ndarray_t *this, ndarray_t *arrayB, size_t send_col_index, size_t rec_col_index)
    {
        isnull(this);
        isnull(arrayB);

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
    