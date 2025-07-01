/**
 * @file io.h
 * @brief Input/Output operations library for ndarray structures
 * 
 * This header file defines functions for loading and saving ndarray data
 * structures from/to various file formats. It provides essential I/O
 * capabilities for data persistence, batch processing, and image handling
 * in numerical computing applications.
 * 
 * The library supports:
 * - Loading numerical data from files with batch processing capabilities
 * - Saving ndarray structures to persistent storage
 * - Image-to-array conversion for computer vision applications
 * - CSV file handling for data science workflows
 * - Flexible file format support with automatic format detection
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 * 
 * @note All file paths should be absolute paths for cross-platform compatibility
 * @warning Ensure sufficient memory is available before loading large datasets
 */

#ifndef IO
#define IO

    #include <ndmath/ndarray.h>

    /* =================================================================== */
    /*                         DATA LOADING FUNCTIONS                     */
    /* =================================================================== */

    /**
     * @brief Loads numerical data from file into ndarray with batch processing
     * 
     * Reads numerical data from a file and constructs an ndarray structure.
     * Supports batch processing to handle large datasets that may not fit
     * entirely in memory. The function can handle various file formats
     * including CSV, binary data, and custom numerical formats.
     * 
     * @param absolute_path Null-terminated string containing the absolute file path
     * @param batch_size Number of elements/rows to process in each batch
     *                   - 0: Load entire file at once (no batching)
     *                   - >0: Process file in chunks of specified size
     * @return ndarray_t New ndarray containing the loaded data
     * 
     * @pre File must exist and be readable
     * @pre absolute_path must be a valid null-terminated string
     * @pre batch_size should be > 0 for large files to prevent memory issues
     * 
     * @post Returned ndarray contains all data from the file
     * @post Memory is allocated for the ndarray data structure
     * 
     * @note Function automatically detects file format based on extension
     * @note For CSV files, assumes comma-separated values with optional headers
     * @note Batch processing is useful for datasets larger than available RAM
     * 
     * @warning Returns invalid ndarray on file read errors
     * @warning Large batch_size values may cause memory allocation failures
     * @warning File format must be supported (numerical data only)
     * 
     * @par Supported File Formats:
     * - .csv: Comma-separated values
     * - .txt: Space or tab-separated numerical data
     * - .dat: Binary or text numerical data
     * - Custom formats (implementation-dependent)
     * 
     * @par Memory Management:
     * Caller is responsible for freeing the returned ndarray memory
     * 
     * @par Example Usage:
     * @code
     * // Load entire file at once
     * ndarray_t data = load_ndarray("/path/to/data.csv", 0);
     * 
     * // Load large file in batches of 1000 rows
     * ndarray_t large_data = load_ndarray("/path/to/big_data.csv", 1000);
     * 
     * // Check if loading was successful
     * if (data.data != NULL) {
     *     // Process data...
     * }
     * @endcode
     * 
     * @par Performance Considerations:
     * - Larger batch sizes reduce I/O overhead but increase memory usage
     * - Smaller batch sizes are memory-efficient but may be slower
     * - Optimal batch size depends on available memory and file size
     */
    extern ndarray_t load_ndarray(const char *absolute_path, size_t batch_size);

    /* =================================================================== */
    /*                         DATA SAVING FUNCTIONS                      */
    /* =================================================================== */

    /**
     * @brief Saves ndarray data to a file
     * 
     * Writes the contents of an ndarray structure to a file in an appropriate
     * format. The output format is determined by the file extension or can be
     * explicitly specified through the filename.
     * 
     * @param this Pointer to the ndarray to be saved
     * @param absolute_path Null-terminated string containing the absolute output file path
     * 
     * @pre this must point to a valid, initialized ndarray
     * @pre absolute_path must be a valid null-terminated string
     * @pre Directory path must exist and be writable
     * @pre ndarray must contain valid data (non-NULL data pointer)
     * 
     * @post File is created/overwritten with ndarray contents
     * @post Data format preserves numerical precision
     * 
     * @note Function automatically determines output format from file extension
     * @note Existing files with the same name will be overwritten
     * @note Output format preserves array dimensions and structure
     * 
     * @warning No error return value - check file system for successful write
     * @warning May fail silently on insufficient disk space or permissions
     * @warning Large arrays may take significant time to write
     * 
     * @par Supported Output Formats:
     * - .csv: Comma-separated values with optional headers
     * - .txt: Human-readable text format with space separation
     * - .dat: Binary format for efficient storage and fast loading
     * - .json: JSON format for interoperability (if supported)
     * 
     * @par Data Preservation:
     * - All numerical values are preserved with full precision
     * - Array dimensions and shape information included
     * - Metadata may be preserved depending on output format
     * 
     * @par Example Usage:
     * @code
     * ndarray_t my_array;
     * // ... initialize and populate my_array
     * 
     * // Save as CSV for human readability
     * save_ndarray(&my_array, "/path/to/output.csv");
     * 
     * // Save as binary for efficiency
     * save_ndarray(&my_array, "/path/to/output.dat");
     * 
     * // Save for later loading
     * save_ndarray(&my_array, "/backup/array_backup.csv");
     * @endcode
     */
    extern void save_ndarray(ndarray_t *this, char *absolute_path);

    /* =================================================================== */
    /*                         IMAGE PROCESSING I/O                       */
    /* =================================================================== */

    /**
     * @brief Converts image file to multi-channel ndarray representation
     * 
     * Loads an image file and converts it into a multi-channel ndarray format
     * suitable for computer vision and image processing operations. Each color
     * channel (RGB) is stored as a separate ndarray for advanced manipulation.
     * 
     * @param absolute_path Null-terminated string containing the absolute path to image file
     * @return nd_image_t Structure containing separate ndarrays for each color channel
     * 
     * @pre Image file must exist and be readable
     * @pre absolute_path must be a valid null-terminated string
     * @pre Image format must be supported
     * 
     * @post Returns nd_image_t with three channel ndarrays (c1, c2, c3)
     * @post Each channel contains pixel intensity values
     * @post Channel dimensions match original image dimensions
     * 
     * @note Function name suggests this may be a placeholder/mock implementation
     * @note Typically c1=Red, c2=Green, c3=Blue for RGB images
     * @note Pixel values are usually normalized to [0.0, 1.0] or [0, 255] range
     * 
     * @warning "fake_" prefix suggests this may be a stub or test function
     * @warning May not handle all image formats correctly
     * @warning Memory allocation required for three separate channel arrays
     * 
     * @par Supported Image Formats:
     * - .bmp: Windows Bitmap (native support via bmp_header structures)
     * - .jpg/.jpeg: JPEG compressed images (requires external library)
     * - .png: Portable Network Graphics (requires external library)
     * - .tiff: Tagged Image File Format (requires external library)
     * 
     * @par Channel Organization:
     * - c1: First color channel (typically Red)
     * - c2: Second color channel (typically Green)  
     * - c3: Third color channel (typically Blue)
     * - Each channel: 2D ndarray with dimensions [height × width]
     * 
     * @par Memory Layout:
     * Each channel is stored as a separate ndarray, allowing independent
     * processing of color channels for advanced image analysis.
     * 
     * @par Example Usage:
     * @code
     * // Load image and separate into channels
     * nd_image_t img = fake_image2array("/path/to/image.bmp");
     * 
     * // Check if loading was successful
     * if (img.c1 != NULL && img.c2 != NULL && img.c3 != NULL) {
     *     // Process individual channels
     *     ndarray_t red_channel = *(img.c1);
     *     ndarray_t green_channel = *(img.c2);
     *     ndarray_t blue_channel = *(img.c3);
     *     
     *     // Perform channel-specific operations...
     * }
     * 
     * // Remember to free memory for each channel
     * // ... cleanup code
     * @endcode
     * 
     * @par Applications:
     * - Color space transformations
     * - Channel-wise filtering and enhancement
     * - Computer vision preprocessing
     * - Machine learning feature extraction
     * - Image segmentation and analysis
     */
    extern nd_image_t fake_image2array(const char *absolute_path);

    /* =================================================================== */
    /*                         FUTURE FUNCTIONALITY                       */
    /* =================================================================== */

    /**
     * @brief CSV dataframe loading functionality (PLANNED)
     * 
     * This functionality is mentioned in the comment but not yet implemented.
     * When available, it would provide specialized CSV loading with dataframe-like
     * features including:
     * 
     * @par Planned Features:
     * - Header row detection and parsing
     * - Column type inference (numeric, string, categorical)
     * - Missing value handling (NaN, empty cells)
     * - Batch processing for large CSV files
     * - Memory-efficient streaming for huge datasets
     * - Column selection and filtering
     * - Data type conversion and validation
     * 
     * @par Expected Interface:
     * @code
     * // Hypothetical future function signature:
     * // ndarray_data_loader load_csv_dataframe(const char* path, 
     * //                                        size_t batch_size,
     * //                                        bool has_header);
     * @endcode
     * 
     * @note This functionality is not currently implemented
     * @note Use load_ndarray() for basic CSV loading needs
     */

#endif /* IO */

/**
 * @section Error Handling
 * 
 * @subsection error_detection Error Detection
 * The I/O functions may fail for various reasons:
 * - File not found or permission denied
 * - Insufficient memory for large datasets
 * - Unsupported file formats
 * - Corrupted or malformed data files
 * - Disk space exhaustion during save operations
 * 
 * @subsection error_checking Error Checking Best Practices
 * @code
 * // Always check return values
 * ndarray_t data = load_ndarray("data.csv", 1000);
 * if (data.data == NULL || data.size == 0) {
 *     fprintf(stderr, "Failed to load data\n");
 *     // Handle error appropriately
 * }
 * 
 * // Check file existence before operations
 * FILE *test = fopen("data.csv", "r");
 * if (test == NULL) {
 *     perror("File access error");
 *     return -1;
 * }
 * fclose(test);
 * @endcode
 * 
 * @section Performance Optimization
 * 
 * @subsection batch_processing Batch Processing Guidelines
 * 
 * Choose appropriate batch sizes based on:
 * - Available system memory
 * - File size and complexity
 * - Processing requirements
 * 
 * @par Recommended Batch Sizes:
 * - Small files (<100MB): batch_size = 0 (load entirely)
 * - Medium files (100MB-1GB): batch_size = 10,000-100,000 rows
 * - Large files (>1GB): batch_size = 1,000-10,000 rows
 * - Adjust based on available RAM and processing needs
 * 
 * @subsection file_format_choice File Format Selection
 * 
 * @par Format Recommendations:
 * - **CSV**: Human-readable, widely compatible, slower I/O
 * - **Binary (.dat)**: Fast I/O, compact storage, not human-readable
 * - **Text (.txt)**: Good compromise, moderate speed and readability
 * 
 * @section Integration Examples
 * 
 * @subsection data_pipeline Complete Data Pipeline
 * @code
 * #include <ndmath/io.h>
 * #include <ndmath/ndarray.h>
 * 
 * int process_dataset(const char* input_path, const char* output_path) {
 *     // Load data with batching for memory efficiency
 *     ndarray_t dataset = load_ndarray(input_path, 5000);
 *     
 *     if (dataset.data == NULL) {
 *         fprintf(stderr, "Failed to load dataset from %s\n", input_path);
 *         return -1;
 *     }
 *     
 *     // Process data (using other ndmath functions)
 *     // ... perform operations on dataset
 *     
 *     // Save processed results
 *     save_ndarray(&dataset, (char*)output_path);
 *     
 *     // Cleanup
 *     // ... free dataset memory
 *     
 *     return 0;
 * }
 * @endcode
 * 
 * @subsection image_processing Image Processing Workflow
 * @code
 * #include <ndmath/io.h>
 * 
 * void process_image(const char* image_path) {
 *     // Load image into separate color channels
 *     nd_image_t img = fake_image2array(image_path);
 *     
 *     if (img.c1 != NULL && img.c2 != NULL && img.c3 != NULL) {
 *         // Process each channel independently
 *         // ... apply filters, transformations, etc.
 *         
 *         // Could save processed channels back to files
 *         save_ndarray(img.c1, "/output/red_channel.csv");
 *         save_ndarray(img.c2, "/output/green_channel.csv");
 *         save_ndarray(img.c3, "/output/blue_channel.csv");
 *         
 *         // Cleanup memory
 *         // ... free channel arrays
 *     }
 * }
 * @endcode
 */