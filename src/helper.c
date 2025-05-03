#include <ndmath/helper.h>
#include <ndmath/error.h>
#include <ndmath/conditionals.h>
#include <math.h>

#define MAX_NUMBER_DECIMAL_PLACES 32


    __always_inline void dpformat(float val, int dp) 
    {
        char formatSpecifier[MAX_NUMBER_DECIMAL_PLACES];
        sprintf(formatSpecifier, " %%.%dlf,", dp);
        printf(formatSpecifier, val);
    }

    __always_inline void print_array(ndarray_t a, size_t dp)
    {
        printf("[");
        for(int i=0; i<(int)a.shape[0]; i++)
        {
            printf(" [");
            for(int j=0; j<(int)a.shape[1]; j++)
            {
                if(dp>32)
                    dp=32;
                dpformat(a.data[i][j], (int)dp);
            }
            printf(" ],");
            if(i == (int)a.shape[0] - 1)
                printf(" ], %ldx%ld\n", a.shape[0], a.shape[1]);
                
            printf("\n");
        }

    }

  
    __always_inline void swap(double *x, double *y)
    {
        double temp;
        temp = *x;
        *x = *y;
        *y = temp;
    }



    inline void clean(ndarray_t* arr, ...) 
    {
        isnull(arr);

        va_list args;
        va_start(args, arr);

        // Iterate over the variable arguments
        ndarray_t* arg;
        while ((arg = va_arg(args, ndarray_t*)) != 0) 
        {
            for(size_t i=0;i<arg->shape[0];i++)
            {
                    free(arg->data[i]);
            }

            free(arg->data);
            free(arg->shape);
            free(arg);

            // For example, clean a resource based on the argument
        }

        va_end(args);

        return;
    }

  


