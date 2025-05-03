#include <ndmath/io.h>
#include <ndmath/error.h>
#include <ndmath/array.h>

    ndarray_t load_ndarray(char *absolute_path)
    {
        size_t i = 0;
        char batch[__MAX__LINE__LENGTH__];
        double List[__MAX__LINES__NUMBER__][__MAX__LINE__LENGTH__];
        char *token;
        FILE *f = fopen(absolute_path, "r");

        if(f==NULL)
        {
            null_error();
        }

        size_t nb_lines = 0;
        size_t nb_cols = 0;
        bool first_line = true;

        
        while((fgets(batch, sizeof(batch), f) != NULL) && (nb_lines < __MAX__LINES__NUMBER__))
        {     
            token = strtok(batch, ";");
            while (token != NULL)
            {
                List[nb_lines][i] = strtod(token, NULL);
                token = strtok(NULL, ";");

                if(first_line)
                {
                    nb_cols++;
                }
                i++;
            }
            first_line = false;
            i = 0;
            nb_lines++;  
        }

        printf("nb_lines = %ld, nb_cols = %ld \n", nb_lines, nb_cols);

        ndarray_t result = array(nb_lines, nb_cols);
        
        for(size_t j = 0;  j<nb_lines; j++)
        {
           for(size_t k = 0; k<nb_cols; k++)
           {
                result.data[j][k] = List[j][k];
           }
        }
            
        
        fclose(f);
        return result;
    }



    void save_ndarray(ndarray_t *this, char *absolute_path)
    {
        FILE *f = fopen(absolute_path, "w");
        if(__MAX__LINE__LENGTH__ < this->shape[1])
            memory_error();
        char batch[__MAX__LINE__LENGTH__];

        if(f==NULL)
        {
            null_error();
        }

        for(size_t j = 0;  j<this->shape[0]; j++)
        {
           for(size_t k = 0; k<this->shape[1]-1; k++)
           {
                snprintf(batch, sizeof(batch), "%lf", this->data[j][k]);
                fprintf(f, "%s;", batch);
           }
                fprintf(f, "%s\n", batch);
                //fprintf(f, "\n");           
        }

       fclose(f);
    }