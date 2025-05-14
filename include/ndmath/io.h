#ifndef IO
#define IO

    #include <ndmath/ndarray.h>


    extern ndarray_t load_ndarray(const char *absolute_path, size_t batch_size);
    extern void save_ndarray(ndarray_t *this, char *absolute_path);
    extern nd_image_t fake_image2array(const char *absolute_path);

    // Load a dataframe from a CSV file with batch size
#endif