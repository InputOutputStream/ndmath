#include <ndmath/statistics.h>
#include <ndmath/operations.h>
#include <ndmath/array.h>
#include <ndmath/error.h>
#include <ndmath/helper.h>
#include <ndmath/conditionals.h>
#include <math.h>

ndarray_t mean (ndarray_t *this, char *axis)
{
    isnull(this);
    
    double temp = 0;
    if(strcmp(axis, "x") == 0)
    {
        ndarray_t result = array(this->shape[0], 1);
        for(int i=0; i<(int)this->shape[0]; i++)
        {
            for(int j=0; j<(int)this->shape[1]; j++)
            {
                temp += this->data[i][j];
            }
            result.data[i][0] = temp;
            result.data[i][0] = result.data[i][0]/(double)this->shape[1];
            temp = 0;
        }
        return result;

    }
    else if(strcmp(axis, "y") == 0)
    {
        ndarray_t result = array(1, this->shape[1]);            
        for(int i=0; i<(int)this->shape[1]; i++)
        {
            for(int j=0; j<(int)this->shape[0]; j++)
            {
                temp += this->data[j][i];
            }
            result.data[0][i] = temp;
            result.data[0][i] = result.data[0][i]/(double)this->shape[0];
            temp = 0;
        }
        return result;

    }
    else if(strcmp(axis, "all") == 0)
    {
        ndarray_t result = array(1, 1);
         if(this->size  == 0)    
        {   
                fprintf(stderr, "Division by zero \n");
                perror("A division by zero occured\n");
                exit(1);
        }

        for(int i=0; i<(int)this->shape[0]; i++)
        {
            for(int j=0; j<(int)this->shape[1]; j++)
            {
                result.data[0][0] += this->data[i][j];
            }
        }
        result.data[0][0] = result.data[0][0]/(double)this->size;
        return result;
    }
    else
    {
            fprintf(stderr, "Unkown Axis\n");
            perror("Provide a valid axis\n");
            clean(this, NULL);
            exit(1);
    }
} 


ndarray_t variance (ndarray_t *this, char *axis)
{
    isnull(this);
    
    if(strcmp("x", axis)==0)
    {
        ndarray_t x_ = mean(this, axis);
        ndarray_t result = array(this->shape[0], 1);
        double temp=0;

        for(int i=0; i<(int)this->shape[0]; i++)
        {
            for(int j=0; j<(int)this->shape[1]; j++)
            {
                temp += (this->data[i][j] - x_.data[i][0]) * (this->data[i][j] - x_.data[i][0]);
            }
            result.data[i][0] = temp/((double)this->shape[1]);
           
            temp = 0;
        }
        clean(&x_, NULL);    
        return result;
    }
    else if (strcmp("y", axis)==0)
    {
        ndarray_t x_ = mean(this, axis);
        ndarray_t result = array(1, this->shape[1]);
        double temp=0;

        for(int i=0; i<(int)this->shape[1]; i++)
        {
            for(int j=0; j<(int)this->shape[0]; j++)
            {
                temp += (this->data[j][i] - x_.data[0][i])*(this->data[j][i] - x_.data[0][i]);
            }
            result.data[0][i] = temp/((double)this->shape[0]);
           
            temp = 0;
        }
        clean(&x_, NULL);
        return result;
    }
    else if (strcmp("all", axis)==0)
    {
        ndarray_t x_ = mean(this, axis);
        ndarray_t result = array(1, 1);

        if(this->size  == 0)    
        {   
            zero_error();
        }

        for(int i=0; i<(int)this->shape[0]; i++)
        {
            for(int j=0; j<(int)this->shape[1]; j++)
            {
                result.data[0][0] += (this->data[i][j] - x_.data[0][0])*(this->data[i][j] - x_.data[0][0]);
            }
        }
        result.data[0][0] = result.data[0][0]/(double)this->size;
        clean(&x_, NULL);

        return result;
    }
    else
    { 
        fprintf(stderr, "Unkown Axis\n");
        perror("Provide a valid axis\n");

        clean(this, NULL);
        exit(1);
    }  
}




ndarray_t std(ndarray_t *this, char *axis)
{
    isnull(this);
    
    if(strcmp("x", axis) == 0)
    {
        ndarray_t result = array(this->shape[0], 1);

        for(int i=0;i<(int)this->shape[0]; i++)
        {
            result.data[i][0] = sqrt(variance(this, axis).data[i][0]);
        }
        return result;
    }

    else if(strcmp("y", axis) == 0)
    {
        ndarray_t result = array(1, this->shape[1]);

        for(int i=0;i<(int)this->shape[1]; i++)
        {
            result.data[0][i] = sqrt(variance(this, axis).data[0][i]);
        }
        return result;
    }

    else if(strcmp("all", axis) == 0)
    {
        ndarray_t result = array(1, 1);

        result.data[0][0] = sqrt(variance(this, axis).data[0][0]);
        return result;
    }
    else
    {
       axis_error(axis);
       clean(this, NULL);
       exit(1);
    }
}

