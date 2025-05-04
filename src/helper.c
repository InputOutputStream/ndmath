#include <ndmath/helper.h>
#include <ndmath/error.h>
#include <ndmath/conditionals.h>
#include <math.h>

#define MAX_NUMBER_DECIMAL_PLACES 32


#define MAX_DP 32

    static __always_inline void dpformat(float val, size_t dp)
    {
        if (dp > MAX_DP) dp = MAX_DP;
        
        char format[MAX_NUMBER_DECIMAL_PLACES];
        snprintf(format, sizeof(format), "%%.%zuf", dp);  // Removed leading space, single %
        printf(format, val);
    }

    __always_inline void print_array(ndarray_t a, size_t dp)
    {
        if (dp > MAX_DP) dp = MAX_DP;
    
        printf("[\n");
        for (size_t i = 0; i < a.shape[0]; i++)
        {
            printf("  [");
            for (size_t j = 0; j < a.shape[1]; j++)
            {
                dpformat(a.data[i][j], (int)dp);
                if (j < a.shape[1] - 1)
                    printf(", ");
            }
            printf("]");
            if (i < a.shape[0] - 1)
                printf(",");
            printf("\n");
        }
        printf("]  // shape: %zux%zu\n", a.shape[0], a.shape[1]);
    }


    void clean(ndarray_t* arr, ...)
    {
        va_list args;
        va_start(args, arr);

        while (arr != NULL)
        {
            if (arr->data != NULL)
            {
                for (size_t i = 0; i < arr->shape[0]; i++)
                {
                    free(arr->data[i]);
                }
                free(arr->data);
                arr->data = NULL;
            }
            arr = va_arg(args, ndarray_t*);
        }

        va_end(args);
    }


    void clean_all_arrays(named_array_t* arrays, size_t count)
    {
        if (!arrays) return;
        
        for (size_t i = 0; i < count; i++)
        {
            if (arrays[i].array){
                printf("Cleaning %s\n", arrays[i].name);
                clean(arrays[i].array, NULL);
                   printf("Cleaned %s\n", arrays[i].name);
                }
        }
    }

    void free_array(ndarray_t *this)
    {
        clean(this, NULL);
        return;
    }

    void print_all_arrays(named_array_t* arrays, size_t count)
    {
        if (!arrays) return;
        
        printf("Named arrays:\n\n");
        for (size_t i = 0; i < count; i++)
        {
            if (arrays[i].array)
            {
                printf("%s:\n", arrays[i].name);
                print_array(*arrays[i].array, 2);
                printf("\n");
            }
        }
    }