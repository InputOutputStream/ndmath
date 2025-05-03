#include <ndmath/trig.h>
#include <math.h>


static inline  double sec(double x);
static double cot(double x);
static double cosec(double x);


// /** Trigonometric functions */
    ndarray_t nd_sin( ndarray_t *this)
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = sin(this->data[i][j]); 
            }    
        }
        return *this;
    }
    
    ndarray_t nd_cos ( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = cos(this->data[i][j]); 
            }    
        }
        return *this;
    }
    ndarray_t nd_tan ( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = tan(this->data[i][j]); 
            }    
        }
        return *this;
    }



    ndarray_t nd_cosh ( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = cosh(this->data[i][j]); 
            }    
        }
        return *this;
    }


    ndarray_t nd_sinh( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = sinh(this->data[i][j]); 
            }    
        }
        return *this;
    }


    ndarray_t nd_tanh ( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = tanh(this->data[i][j]); 
            }    
        }
        return *this;
    }

    ndarray_t nd_sec ( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = sec(this->data[i][j]); 
            }    
        }
        return *this;
    }


    ndarray_t nd_cot( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = cot(this->data[i][j]); 
            }    
        }
        return *this;
    }



    ndarray_t nd_cosec( ndarray_t *this )
    {
        if(this == NULL)
        {
            fprintf(stderr, "NULL POINTER\n");
            perror("POINTER TO VOID PROVIDED\n");
            exit(1);
        }
        size_t i, j;
        for(i=0; i<this->shape[0]; i++)
        {
            for(j=0; j<this->shape[1]; i++)
            {
                this->data[i][j] = cosec(this->data[i][j]); 
            }    
        }
        return *this;
    }

    static inline double sec(double x)
    {
        return 1/(cos(x));
    }

    static inline double cosec(double x)
    {   
        return 1/(sin(x));
    }

    static inline double cot(double x)
    {
        return 1/(tan(x));
    }