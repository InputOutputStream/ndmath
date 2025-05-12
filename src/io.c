#include <ndmath/io.h>
#include <ndmath/error.h>
#include <ndmath/array.h>
#include <ndmath/conditionals.h>


    const size_t __MAX__LINE__LENGTH__ = 4096;
    const size_t __MAX__LINES__NUMBER__ = 1024;

    static char detect_delimiter(const char *path);

    
    // Detect the delimiter in a CSV file
    static char detect_delimiter(const char *path) {
        FILE *file = fopen(path, "r");
        if (!file) {
            fprintf(stderr, "ERROR: Could not open file %s\n", path);
            exit(1);
        }

        char line[__MAX__LINE__LENGTH__];
        if (!fgets(line, __MAX__LINE__LENGTH__, file)) {
            fclose(file);
            fprintf(stderr, "ERROR: Empty file %s\n", path);
            exit(1);
        }

        // Common delimiters to check
        const char *delimiters = ",;\t ";
        int counts[4] = {0}; // Counts for comma, semicolon, tab, space
        int max_count = 0;
        char best_delimiter = ','; // Default to comma

        // Count occurrences of each delimiter
        for (int i = 0; line[i] && line[i] != '\n'; i++) {
            for (int j = 0; j < 4; j++) {
                if (line[i] == delimiters[j]) {
                    counts[j]++;
                    if (counts[j] > max_count) {
                        max_count = counts[j];
                        best_delimiter = delimiters[j];
                    }
                }
            }
        }

        // Validate the delimiter by checking field consistency
        if (max_count > 0) {
            // Count fields in the first line
            char *line_copy = strdup(line);
            char *token = strtok(line_copy, &best_delimiter);
            int field_count = 0;
            while (token) {
                field_count++;
                token = strtok(NULL, &best_delimiter);
            }
            free(line_copy);

            // Check the next line (if available) for consistency
            if (fgets(line, __MAX__LINE__LENGTH__, file)) {
                line_copy = strdup(line);
                token = strtok(line_copy, &best_delimiter);
                int next_field_count = 0;
                while (token) {
                    next_field_count++;
                    token = strtok(NULL, &best_delimiter);
                }
                free(line_copy);

                // If field counts differ, fallback to comma
                if (next_field_count != field_count) {
                    best_delimiter = ',';
                }
            }
        }

        fclose(file);
        return best_delimiter;
    }

    // Load an ndarray from a CSV file with batch size and non-numeric handling
    ndarray_t load_ndarray(const char *absolute_path, size_t batch_size) {

        if (batch_size == 0) {
            batch_size = __MAX__LINES__NUMBER__;
        }

        // Detect the delimiter
        char delimiter = detect_delimiter(absolute_path);
        char delim_str[2] = {delimiter, '\0'}; // For strtok

        FILE *file = fopen(absolute_path, "r");
        if (file == NULL) {
            perror("ERROR: POINTER TO VOID PROVIDED");
            exit(EXIT_FAILURE);
        }

        // Count rows and columns
        size_t rows = 0;
        size_t cols = 0;
        char line[__MAX__LINE__LENGTH__];
        char *line_copy;
        bool first_line = true;

        while (fgets(line, __MAX__LINE__LENGTH__, file) && rows < batch_size) {
            if (first_line) {
                line_copy = strdup(line);
                char *token = strtok(line_copy, delim_str);
                while (token) {
                    cols++;
                    token = strtok(NULL, delim_str);
                }
                free(line_copy);
                first_line = false;
            }
            rows++;
        }
        rewind(file);

        // Allocate the array
        ndarray_t arr = array(rows, cols);
        isnull(&arr);

        // Read and parse the file
        size_t row = 0;
        while (fgets(line, __MAX__LINE__LENGTH__, file) && row < rows) {
            line_copy = strdup(line);
            char *token = strtok(line_copy, delim_str);
            size_t col = 0;
            while (token && col < cols) {
                // Remove trailing newline or whitespace
                token[strcspn(token, "\n\r")] = '\0';

                // Convert token to double, handling non-numeric values
                char *endptr;
                errno = 0;
                double value = strtod(token, &endptr);

                if (endptr == token || *endptr != '\0' || errno == ERANGE) {
                    // Non-numeric or out-of-range value
                    fprintf(stderr, "WARNING: Non-numeric value '%s' at row %zu, col %zu; using 0.0\n",
                            token, row, col);
                    arr.data[row][col] = 0.0;
                } else {
                    arr.data[row][col] = value;
                }

                token = strtok(NULL, delim_str);
                col++;
            }
            free(line_copy);
            row++;
        }

        fclose(file);
        return arr;
    }


    //save the ndarray into a file
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
        }

       fclose(f);
    }
/*
    Above methods are used on ndarrays and the below ones on dataframes
*/

    