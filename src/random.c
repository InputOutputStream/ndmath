#include <ndmath/random.h>

#include <ndmath/helper.h>
#include <ndmath/array.h>
#include <math.h>


#define  MAX_RAND 100
#define  MIN_RAND 2

static inline void swap(double *x, double *y);


void lcg64_seed(lcg64_t *gen, uint64_t seed) {
    gen->seed = seed;
}

uint64_t lcg64_next(lcg64_t *gen) {
    gen->seed = (LCG_A * gen->seed + LCG_C) % LCG_M;
    return gen->seed;
}

// Convert to [0, 1)
double lcg64_next_uniform(lcg64_t *gen) {
    return (double)lcg64_next(gen) / (double)LCG_M;
}

// Convert to integer in range [min, max]
int lcg64_randint(lcg64_t *gen, int min, int max) {
    return (int)(lcg64_next(gen) % (max - min + 1)) + min;
}



/** Random number array generation */
    ndarray_t rand_array(int max, int min)
    {
        lcg64_t gen;
        lcg64_seed(&gen, (uint64_t)time(NULL));

        size_t rows = lcg64_randint(&gen,MIN_RAND, MAX_RAND);
        size_t cols = lcg64_randint(&gen,MIN_RAND, MAX_RAND);

        if(max < min)
        {
            fprintf(stderr, "Error\n");
            perror("Max is less than min\n");
            exit(EXIT_FAILURE);
        }
        ndarray_t result = array(rows, cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
               result.data[i][j] = lcg64_next_uniform(&gen);
            }
        }
        return result;
    }

    ndarray_t randu(size_t rows, size_t cols, size_t random_state)
    {
        lcg64_t gen;
        lcg64_seed(&gen, random_state);

        ndarray_t result = array(rows, cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                result.data[i][j] = lcg64_next_uniform(&gen); 
            }
        }
        return result;
    }

    ndarray_t randn(size_t rows, size_t cols, size_t random_state)
    {

        srand(random_state);   
        ndarray_t result = array(rows, cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                double u1 = ((double)rand() / RAND_MAX);
                double u2 = ((double)rand() / RAND_MAX);
                double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
             
                result.data[i][j] = z0; 
            }
        }
        return result;
    }

    ndarray_t randint(size_t rows, size_t cols, int max, int min, size_t random_state)
    {
        lcg64_t gen;
        lcg64_seed(&gen, random_state);
      
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
                result.data[i][j] = lcg64_randint(&gen, min, max);
            }
        }
        return result;
    }


    ndarray_t shuffle(ndarray_t *this, size_t random_state)
    {
        if (!this)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(EXIT_FAILURE);
        }
    
        srand(random_state);
        size_t rows = this->shape[0];
        size_t cols = this->shape[1];
        size_t total = rows * cols;
    
        // Copier les données
        ndarray_t result = copy(this);
    
        // Aplatir
        double *flat = malloc(total * sizeof(double));
        if (!flat) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    
        size_t index = 0;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                flat[index++] = result.data[i][j];
    
        // Shuffle de Fisher-Yates sur flat
        for (size_t i = total - 1; i > 0; i--) {
            size_t j = rand() % (i + 1);
            swap(&flat[i], &flat[j]);
        }
    
        // Réinjecter dans la matrice 2D
        index = 0;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result.data[i][j] = flat[index++];
    
        free(flat);
        return result;
    }

    ndarray_t randperm(size_t n, uint64_t seed)
    {
        lcg64_t gen;
        lcg64_seed(&gen, seed);
        
        ndarray_t result = array(1, n);
        for (size_t i = 0; i < n; i++)
            result.data[0][i] = i;

        for (size_t i = n - 1; i > 0; i--) {
            size_t j = lcg64_next(&gen) % (i + 1);
            swap(&result.data[0][i], &result.data[0][j]);
        }

        return result;
    }

    

    static inline void swap(double *x, double *y)
    {
        double temp;
        temp = *x;
        *x = *y;
        *y = temp;
    }