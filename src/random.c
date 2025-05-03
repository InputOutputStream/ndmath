#include <ndmath/random.h>

#include <ndmath/helper.h>
#include <ndmath/array.h>
#include <math.h>


/** Random number generation */
    // ndarray_t rand(size_t rows, size_t cols, int max, int min)
    // {
    //     if(max < min)
    //     {
    //         fprintf(stderr, "Error\n");
    //         perror("Max is less than min\n");
    //         exit(EXIT_FAILURE);
    //     }
    //     srand(time(NULL));
    //     ndarray_t result = array(rows, cols);
    //     for (size_t i = 0; i < rows; i++)
    //     {
    //         for (size_t j = 0; j < cols; j++)
    //         {
    //             result.data[i][j] = (double)(rand() % max) + min; 
    //         }
    //     }
    //     return result;
    // }

    ndarray_t randn(size_t rows, size_t cols, size_t random_state)
    {
        srand(random_state);
        ndarray_t result = array(rows, cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                result.data[i][j] = ((double)rand()/(double)RAND_MAX); 
            }
        }
        return result;
    }

    ndarray_t randint(size_t rows, size_t cols, int max, int min, size_t random_state)
    {
        if(max < min)
        {
            fprintf(stderr, "Error\n");
            perror("Max is less than min\n");
            exit(EXIT_FAILURE);
        }
        srand(random_state);
        ndarray_t result = array(rows, cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                result.data[i][j] = (double)(rand() % max) + min; 
            }
        }
        return result;
    }

    ndarray_t shuffle(ndarray_t *this, int random_state)
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        int indexi, indexj;
        srand(random_state);
        ndarray_t result = copy(this);
        for (size_t i = 0; i < this->shape[0]; i++)
        {
            for (size_t j = 0; j < this->shape[1]; j++)
            {
               indexj = (double)(rand() % this->shape[1]); 
               indexi = (double)(rand() % this->shape[0]); 
               swap(&result.data[i][j], &result.data[i][indexj]);
               swap(&result.data[i][j], &result.data[indexi][j]);
            }
        }
        return result;
    }
    // ndarray_t choice(int m, int n)
    // {

    // }

