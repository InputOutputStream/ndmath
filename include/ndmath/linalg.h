/**
 * @file linalg.h
 * @brief Linear algebra operations library for ndarray structures
 * 
 * This header file defines a comprehensive set of linear algebra operations
 * for n-dimensional arrays. It provides fundamental mathematical operations
 * commonly used in scientific computing, machine learning, and numerical analysis.
 * 
 * The library includes:
 * - Matrix decompositions (QR, SVD, Eigenvalue)
 * - Matrix operations (multiplication, inversion, determinant)
 * - Vector operations (dot product, outer product, norms)
 * - Advanced numerical algorithms with iterative solvers
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 * 
 * @note All functions assume well-formed ndarray_t structures as input
 * @warning Some operations may be computationally intensive for large matrices
 */

#ifndef LINALG
#define LINALG

    #include <ndmath/ndarray.h>

    /* =================================================================== */
    /*                       MATRIX PROPERTIES                            */
    /* =================================================================== */

    /**
     * @brief Computes the determinant of a square matrix
     * 
     * Calculates the determinant of a square matrix using appropriate numerical
     * methods. The determinant is a scalar value that provides important
     * information about the matrix properties (invertibility, volume scaling).
     * 
     * @param this Pointer to a square ndarray matrix
     * @return double The determinant value
     * 
     * @note Matrix must be square (n×n) for determinant calculation
     * @warning Returns NaN or undefined value for non-square matrices
     * @warning Large matrices may suffer from numerical instability
     * 
     * @par Time Complexity:
     * O(n³) for general matrices using LU decomposition
     * 
     * @par Example:
     * @code
     * ndarray_t matrix; // 3x3 matrix
     * double det_value = det(&matrix);
     * if (det_value != 0.0) {
     *     printf("Matrix is invertible\n");
     * }
     * @endcode
     */
    extern double det(ndarray_t *this);

    /**
     * @brief Computes matrix norms along specified axis
     * 
     * Calculates various matrix norms depending on the axis parameter.
     * Supports different norm types commonly used in numerical analysis.
     * 
     * @param this Pointer to the input ndarray
     * @param axis String specifying the norm type and axis:
     *             - "fro" or "F": Frobenius norm (default for matrices)
     *             - "1": 1-norm (maximum column sum)
     *             - "2": 2-norm (spectral norm, largest singular value)
     *             - "inf": Infinity norm (maximum row sum)
     *             - NULL: Defaults to Frobenius norm
     * @return ndarray_t New ndarray containing the computed norm(s)
     * 
     * @note For vectors, returns the corresponding vector norm
     * @note For matrices, interpretation depends on the axis parameter
     * 
     * @par Mathematical Definition:
     * - Frobenius: ||A||_F = sqrt(sum(|a_ij|²))
     * - 1-norm: ||A||_1 = max_j(sum_i(|a_ij|))
     * - ∞-norm: ||A||_∞ = max_i(sum_j(|a_ij|))
     */
    extern ndarray_t norm(ndarray_t *this, char *axis);

    /* =================================================================== */
    /*                       MATRIX OPERATIONS                            */
    /* =================================================================== */

    /**
     * @brief Computes the matrix inverse
     * 
     * Calculates the inverse of a square matrix using numerical methods
     * such as LU decomposition with partial pivoting or Gauss-Jordan elimination.
     * 
     * @param this Pointer to a square, invertible ndarray matrix
     * @return ndarray_t New ndarray containing the matrix inverse
     * 
     * @pre Matrix must be square and non-singular (det(A) ≠ 0)
     * @post Result satisfies: A × A⁻¹ = I (identity matrix)
     * 
     * @warning Returns invalid result for singular or near-singular matrices
     * @warning Numerical errors can accumulate for ill-conditioned matrices
     * @note Consider using pseudo-inverse for non-square or rank-deficient matrices
     * 
     * @par Time Complexity:
     * O(n³) for n×n matrices
     * 
     * @par Numerical Stability:
     * Check condition number before inversion for numerical stability
     */
    extern ndarray_t inv(ndarray_t *this);

    /**
     * @brief Matrix multiplication (linear algebra product)
     * 
     * Performs standard matrix multiplication between two matrices.
     * Computes C = A × B where the number of columns in A must equal
     * the number of rows in B.
     * 
     * @param this Pointer to the left matrix operand (m×k)
     * @param arrayB Pointer to the right matrix operand (k×n)
     * @return ndarray_t New ndarray containing the matrix product (m×n)
     * 
     * @pre Inner dimensions must match: A.cols == B.rows
     * @post Result dimensions: (A.rows × B.cols)
     * 
     * @note This is true matrix multiplication, not element-wise multiplication
     * @warning Function behavior undefined if dimension requirements not met
     * 
     * @par Time Complexity:
     * O(m×n×k) for matrices of size m×k and k×n
     * 
     * @par Mathematical Definition:
     * C[i][j] = Σ(k=0 to K-1) A[i][k] × B[k][j]
     */
    extern ndarray_t matmul(ndarray_t *this, ndarray_t *arrayB);

    /* =================================================================== */
    /*                        VECTOR OPERATIONS                           */
    /* =================================================================== */

    /**
     * @brief Computes the dot product of two vectors
     * 
     * Calculates the inner product (dot product) between two column vectors.
     * For vectors u and v, computes u·v = Σ(u[i] × v[i]).
     * 
     * @param a Pointer to the first vector (column vector)
     * @param b Pointer to the second vector (column vector)
     * @return ndarray_t Scalar result as a 1×1 ndarray
     * 
     * @pre Both vectors must have the same length
     * @pre Vectors should be column vectors (n×1 matrices)
     * @post Result is a scalar value in ndarray format
     * 
     * @note Returns scalar product, not element-wise multiplication
     * @warning Undefined behavior if vector dimensions don't match
     * 
     * @par Mathematical Definition:
     * a·b = Σ(i=0 to n-1) a[i] × b[i]
     * 
     * @par Geometric Interpretation:
     * |a| × |b| × cos(θ) where θ is the angle between vectors
     */
    extern ndarray_t dot(ndarray_t* a, ndarray_t* b);

    /**
     * @brief Computes the outer product of two vectors
     * 
     * Calculates the outer product between two vectors, resulting in a matrix.
     * For vectors u (m×1) and v (n×1), computes the matrix A where A[i][j] = u[i] × v[j].
     * 
     * @param a Pointer to the first vector (m×1)
     * @param b Pointer to the second vector (n×1)
     * @return ndarray_t New ndarray containing the outer product matrix (m×n)
     * 
     * @pre Input arrays should be vectors (single column)
     * @post Result is a matrix with dimensions (len(a) × len(b))
     * 
     * @note Result matrix has rank 1 (all rows are scalar multiples of each other)
     * @note Also known as tensor product for vectors
     * 
     * @par Mathematical Definition:
     * (a ⊗ b)[i][j] = a[i] × b[j]
     * 
     * @par Applications:
     * - Computing covariance matrices
     * - Rank-1 updates in optimization
     * - Quantum mechanics (tensor products)
     */
    extern ndarray_t outer(ndarray_t* a, ndarray_t* b);

    /* =================================================================== */
    /*                      MATRIX DECOMPOSITIONS                         */
    /* =================================================================== */

    /**
     * @brief Computes eigenvalues using iterative methods
     * 
     * Calculates the eigenvalues of a square matrix using iterative algorithms
     * such as the power method or QR algorithm. The number of iterations
     * controls the precision of the result.
     * 
     * @param this Pointer to a square ndarray matrix
     * @param nbiters Number of iterations for the eigenvalue algorithm
     * @return ndarray_t New ndarray containing the eigenvalues
     * 
     * @pre Matrix must be square
     * @note Higher iteration count generally improves accuracy
     * @note For symmetric matrices, eigenvalues are guaranteed to be real
     * @warning Complex eigenvalues may not be handled correctly
     * @warning Convergence not guaranteed for all matrices
     * 
     * @par Time Complexity:
     * O(n³ × nbiters) for n×n matrices
     * 
     * @par Numerical Considerations:
     * - Increase nbiters for better precision
     * - Some matrices may require special handling (defective matrices)
     * - Consider matrix conditioning for numerical stability
     */
    extern ndarray_t eig(ndarray_t *this, size_t nbiters);

    /**
     * @brief Computes Singular Value Decomposition (SVD)
     * 
     * Performs SVD factorization of a matrix: A = U × Σ × V^T
     * where U and V are orthogonal matrices and Σ is diagonal with non-negative entries.
     * 
     * @param this Pointer to the input ndarray matrix (m×n)
     * @return ndarray_t Structure containing the SVD components
     * 
     * @note SVD exists for any matrix (not just square matrices)
     * @note Singular values are returned in descending order
     * @post U is m×m orthogonal, V is n×n orthogonal, Σ is m×n diagonal
     * 
     * @warning Return format needs clarification (single array vs. multiple arrays)
     * @note SVD is fundamental for many numerical algorithms
     * 
     * @par Applications:
     * - Principal Component Analysis (PCA)
     * - Least squares problems
     * - Matrix rank determination
     * - Pseudoinverse computation
     * - Data compression and dimensionality reduction
     * 
     * @par Mathematical Properties:
     * - ||A||_2 = σ_max (largest singular value)
     * - rank(A) = number of non-zero singular values
     * - cond(A) = σ_max / σ_min (condition number)
     */
    extern ndarray_t svd(ndarray_t *this);

    /**
     * @brief Computes QR decomposition of a matrix
     * 
     * Performs QR factorization: A = Q × R where Q is orthogonal and R is upper triangular.
     * This is an in-place decomposition that modifies the provided Q and R matrices.
     * 
     * @param this Pointer to the input matrix to decompose (m×n)
     * @param Q Pointer to pre-allocated ndarray for orthogonal matrix (m×m)
     * @param R Pointer to pre-allocated ndarray for upper triangular matrix (m×n)
     * 
     * @pre Q and R must be pre-allocated with correct dimensions
     * @pre this should be m×n matrix where m ≥ n for standard QR
     * @post Q is orthogonal: Q^T × Q = I
     * @post R is upper triangular: R[i][j] = 0 for i > j
     * @post A = Q × R (original matrix reconstructed)
     * 
     * @note This function modifies Q and R arrays in-place
     * @note Uses algorithms like Gram-Schmidt or Householder reflections
     * @warning Ensure Q and R are properly allocated before calling
     * 
     * @par Applications:
     * - Solving linear least squares problems
     * - Eigenvalue computation (QR algorithm)
     * - Orthogonalization of vectors
     * - Numerical stability in linear algebra
     * 
     * @par Time Complexity:
     * O(mn²) for m×n matrix using Householder method
     * 
     * @par Example Usage:
     * @code
     * ndarray_t A, Q, R;
     * // Initialize A with data, allocate Q and R
     * qr(&A, &Q, &R);
     * // Now Q and R contain the decomposition
     * @endcode
     */
    extern void qr(ndarray_t *this, ndarray_t *Q, ndarray_t *R);

#endif /* LINALG */

/**
 * @section Performance Notes
 * 
 * @subsection computational_complexity Computational Complexity
 * The computational complexity of linear algebra operations varies significantly:
 * 
 * - **O(n)**: Vector operations (dot product, norms)
 * - **O(n²)**: Outer product, matrix-vector multiplication
 * - **O(n³)**: Matrix multiplication, inversion, decompositions
 * - **O(n³ × k)**: Iterative methods (eigenvalues with k iterations)
 * 
 * @subsection numerical_stability Numerical Stability
 * 
 * Consider the following for numerical stability:
 * - Check condition numbers before matrix inversion
 * - Use SVD for rank-deficient or nearly singular systems
 * - Increase iteration counts for iterative methods when higher precision is needed
 * - Be aware of floating-point precision limitations
 * 
 * @section Usage Examples
 * 
 * @subsection basic_operations Basic Matrix Operations
 * @code
 * // Matrix multiplication
 * ndarray_t A, B, C;
 * // ... initialize A and B
 * C = matmul(&A, &B);
 * 
 * // Compute determinant and inverse
 * double det_A = det(&A);
 * if (fabs(det_A) > 1e-12) {  // Check for numerical zero
 *     ndarray_t A_inv = inv(&A);
 *     // Use A_inv...
 * }
 * @endcode
 * 
 * @subsection decompositions Matrix Decompositions
 * @code
 * // QR decomposition
 * ndarray_t A, Q, R;
 * // ... initialize A, allocate Q and R with proper dimensions
 * qr(&A, &Q, &R);
 * 
 * // SVD for dimensionality reduction
 * ndarray_t U_sigma_Vt = svd(&A);
 * 
 * // Eigenvalue computation
 * size_t iterations = 1000;
 * ndarray_t eigenvals = eig(&A, iterations);
 * @endcode
 * 
 * @subsection vector_operations Vector Operations
 * @code
 * // Dot product
 * ndarray_t u, v, dot_result;
 * // ... initialize vectors u and v
 * dot_result = dot(&u, &v);
 * 
 * // Outer product for rank-1 matrix
 * ndarray_t outer_matrix = outer(&u, &v);
 * 
 * // Vector norm
 * ndarray_t norm_result = norm(&u, "2");  // L2 norm
 * @endcode
 */