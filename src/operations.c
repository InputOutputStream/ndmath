#include <ndmath/operations.h>

#include <ndmath/helper.h>
#include <ndmath/array.h>
#include <ndmath/error.h>
#include <ndmath/conditionals.h>
#include <math.h>


#pragma GCC push_options
    #pragma GCC optimize("O1,unroll-loops")
/** Array operations */



    ndarray_t sum(ndarray_t *this,  ndarray_t *arrayB)
    {
        isnull(this);
        isnull(arrayB);

        ndarray_t result = {0};
        if(this->shape[0] == arrayB->shape[0] && this->shape[1] == arrayB->shape[1])
        {
            result = array(this->shape[0], this->shape[1]);
            for(int i=0; i<(int)this->shape[0]; i++)
            {
                for(int j=0; j<(int)this->shape[1]; j++)
                {
                    result.data[i][j] = this->data[i][j] + arrayB->data[i][j];
                }
            }
            return result;
        }
        else
        {
            fprintf(stderr, "Invalid dimensions %ldx%ld and %ldx%ld for array addition\n", this->shape[0], this->shape[1], arrayB->shape[0], arrayB->shape[1]);
            perror("Use valid ndarray_t dimesions please\n");
            exit(1);
        }
        
    }

    ndarray_t subtract (ndarray_t *this, ndarray_t *arrayB)
    {
        isnull(this);
        isnull(arrayB);
        
        ndarray_t result  = {0};
        if(this->shape[0] == arrayB->shape[0] && this->shape[1] == arrayB->shape[1])
        {
            result = array(this->shape[0], this->shape[1]);
            for(int i = 0; i<(int)this->shape[0]; i++)
                {
                    for(int j=0; j<(int)this->shape[1]; j++)
                    {
                        result.data[i][j] = this->data[i][j] - arrayB->data[i][j];
                    }
                }
            return result;
        }
        else
        {
            fprintf(stderr, "Invalid dimensions %ldx%ld and %ldx%ld for array subtraction\n", this->shape[0], this->shape[1], arrayB->shape[0], arrayB->shape[1]);
            perror("Use valid ndarray_t dimesions please\n");
            exit(1);
        }
    }



    ndarray_t ravel(ndarray_t *this)
    {
        isnull(this);
        
        int i, j, k=0;
        ndarray_t result = array(1, this->size);
        
        for(i=0; i<(int)this->shape[0]; i++)
        {
            for(j=0; j<(int)this->shape[1]; j++)
            {
                result.data[0][k] = this->data[i][j];
                k++; 
            }
        }
        return result;
    }


    ndarray_t scaler (ndarray_t *this, double sc, char op)
    {
        isnull(this);
        
        int i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<(int)this->shape[0]; i++)
        {
            for(j=0; j<(int)this->shape[1]; j++)
            {
                if(op == '+')
                    result.data[i][j] = this->data[i][j] + sc;
                else if(op == '*')
                    result.data[i][j] = this->data[i][j] * sc;
                else if(op == '-')
                    result.data[i][j] = this->data[i][j] - sc;
                else if(op == '/')
                {
                    if(sc  == 0)    
                    {
                        fprintf(stderr, "Division by zero \n");
                        perror("A division by zero occured\n");
                        exit(1);
                    }
                    result.data[i][j] = this->data[i][j] / sc;
                }
                else
                {
                    fprintf(stderr, "Invalid arithmetic operator %c \n", op);
                    perror("Use valid arithmetic operator please\n");
                    exit(1);
                }
            }
        }
        return result;
    }

    ndarray_t divide(ndarray_t *this, ndarray_t *arrayB)
    {
        isnull(this);
        isnull(arrayB);
        
        if(this->shape[0] != arrayB->shape[0] || this->shape[1] != arrayB->shape[1])
        {
            fprintf(stderr, "Invalid dimensions %ldx%ld and %ldx%ld for element wise division\n", this->shape[0], this->shape[1], arrayB->shape[0], arrayB->shape[1]);
            perror("Use valid ndarray_t dimesions please\n");
            exit(1);
        }

        int i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<(int)this->shape[0]; i++)
        {
            for(j=0; j<(int)this->shape[1]; j++)
            {
                if(arrayB->data[i][j]  == 0)    
                {
                    fprintf(stderr, "Division by zero \n");
                    perror("A division by zero occured\n");
                    exit(1);
                }
                result.data[i][j] = this->data[i][j]/arrayB->data[i][j];
            }
        }
        return result;
    }
    
  
    ndarray_t nd_log(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = log10(this->data[i][j]);
            }
        }
        return result;
    }

    //Creates a new variable containing the transposed version of the previous matrix
    ndarray_t transpose (ndarray_t *this)
    {
        isnull(this);
        
        int i, j;
        ndarray_t result = array(this->shape[1], this->shape[0]);
        for(i=0; i<(int)this->shape[0]; i++)
        {
            for(j=0; j<(int)this->shape[1]; j++)
            {
                result.data[j][i] = this->data[i][j];
            }
        }

        return result;
    }

    ndarray_t power(ndarray_t *this, double exponent)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = pow(this->data[i][j], exponent);
            }
        }
        return result;
    }

    inline ndarray_t nd_log2(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = log2(this->data[i][j]);
            }
        }
        return result;
    }

    inline ndarray_t nd_exp(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = exp(this->data[i][j]);
            }
        }
        return result;
    }

    
    inline ndarray_t neg(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
               
                result.data[i][j] = this->data[i][j] * -1;
            }
        }
        return result;
    }

    inline ndarray_t square(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                    result.data[i][j] = this->data[i][j] * this->data[i][j];
            }
        }
        return result;
    }

    
    inline ndarray_t cube(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = this->data[i][j] * this->data[i][j] * this->data[i][j];
            }
        }
        return result;
    }

    
    inline ndarray_t nd_abs(ndarray_t *this)
    {
        isnull(this);

        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = fabs(this->data[i][j]);
            }
        }
        return result;
    }

    
    inline ndarray_t nd_sqrt(ndarray_t *this)
    {
        isnull(this);
        
        size_t i, j;
        ndarray_t result = array(this->shape[0], this->shape[1]);
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0;j<this->shape[1]; j++)
            {
                result.data[i][j] = sqrt(this->data[i][j]);
            }
        }
        return result;  
    }

    #pragma GCC pop_options


 