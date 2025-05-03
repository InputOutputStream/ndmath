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

    ndarray_t ones (size_t rows, size_t cols)
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
        double spacing = (double)((max)/result.size);
        
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
            clean(this, NULL);
            axis_error(axis);
            exit(1);
        } 
    }

    ndarray_t argmax(ndarray_t *this, char *axis)
    {
        if(this == NULL)
        {
            clean(this, NULL);
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
            clean(this, NULL);
            axis_error(axis);
            exit(1);
        } 
    }


    ndarray_t trill(double fill, size_t rows, size_t cols)
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

    ndarray_t trilup(double fill, size_t rows, size_t cols)
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
            clean(arrayB, NULL);
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
        if(this == NULL)
        {
            clean(this, NULL);
            null_error();
        }
        
        if(new_cols*new_rows != this->size)
        {
            dimension_error(this, new_cols, new_rows);
        }
        
        ndarray_t result = array(new_rows, new_cols);
        size_t index = 0, oindex = 0;

        for(size_t i = 0; i<new_cols; i++)
        {
            for(size_t j = 0; j<new_rows; j++)
            {
                oindex = i * this->shape[0] + j;
                result.data[i][j] = this->data[i][oindex];
                index++;
            }
            index = 0;
        }


        return result;
    }



    ndarray_t rslice (ndarray_t *this, size_t rows_start, size_t rows_stop)
    {
        if (rows_start >= this->shape[0] || rows_stop > this->shape[0] || rows_start > rows_stop) 
        {
            clean(this, NULL);
            index_error();
        }

        double **slice = &this->data[rows_start];  // Create a pointer to the row_indexth element
        double **end = &this->data[rows_stop];    
        size_t slice_size = end - slice + 1;  // Calculate the size of the slice

        // Iterate over the slice and print its elements
        ndarray_t result = array(slice_size, this->shape[1]);
        for (size_t i = 0; i < slice_size; i++)
        {
            for(size_t j=0; j<this->shape[1]; j++)
            {
                result.data[i][j] = slice[i][j];
            }
        }
       return result;
    }
    


    ndarray_t cslice (ndarray_t *this, size_t col_start, size_t col_stop)
    {
        //printf("AM STUCK HERE\n");

        if (col_start >= this->shape[1] || col_stop > this->shape[1] || col_start > col_stop) 
        {
            clean(this, NULL);
            index_error();        
        }

        ndarray_t temp = transpose(this);

        double **slice = &temp.data[col_start];  // Create a pointer to the ith_col element
        double **end = &temp.data[col_stop];    
        size_t slice_size = end - slice + 1;  // Calculate the size of the slice

        // Iterate over the slice and print its elements
        ndarray_t result = array(slice_size, temp.shape[1]);

        for (size_t i = 0; i <slice_size; i++)
        {
            for(size_t j=0; j<temp.shape[1]; j++)
            {
                result.data[i][j] = slice[i][j];
            }
        }

        clean(&temp, NULL);
        result = transpose(&result);
        return result;
    }



    ndarray_t rassign(ndarray_t *this, ndarray_t *arrayB, size_t row_index)
    {
        if(this->shape[1] != arrayB ->shape[1])
        {
            clean(this, NULL);
            clean(arrayB, NULL);
            mat_error();
        }

        //size_t k = 0;
        
        for(size_t i=0;i<this->shape[0];i++)
        {
            for(size_t j=0; j<this->shape[1]; j++)
            {
                if(i == row_index)
                    this->data[i][j] = arrayB->data[0][j];
            }
                if(i == row_index)
                    break;
        }
        
        return *this;
    }

    ndarray_t cassign(ndarray_t *this, ndarray_t *arrayB, size_t col_index)
    {
        if(this->shape[0] != arrayB->shape[0])
        {
            clean(this, NULL);
            clean(arrayB, NULL);
            mat_error();
            
        }
        
        //size_t k = 0;

        for(size_t i=0;i<this->shape[0];i++)
        {
            for(size_t j=0; j<this->shape[1]; j++)
            {
                if(j == col_index)
                    this->data[i][j] = arrayB->data[i][0];
            }
        }
        
        return *this;
    }

