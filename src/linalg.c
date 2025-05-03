#include <ndmath/linalg.h>

#include <ndmath/helper.h>
#include <ndmath/array.h>
#include <ndmath/error.h>
#include <ndmath/conditionals.h>
#include <ndmath/operations.h>
#include <math.h>


    ndarray_t inv(ndarray_t *this)
    {
        isnull(this);
        issquare(this);

        ndarray_t I = identity(this->shape[0], this->shape[1]);
        ndarray_t arr = copy(this);

        size_t i=0, j=0, k=0;

        for(j=0; j<arr.shape[0]; j++)//j
        {
            double pivot = arr.data[j][j];

            for(k=0; k<arr.shape[0]; k++)//k
            {
                arr.data[j][k] = arr.data[j][k]/pivot;
                I.data[j][k] = I.data[j][k]/pivot;
            }

            for(i=0; i<this->shape[0]; i++)//i
            {
                if(j!=i)
                {
                    double coef = arr.data[i][j];

                    for(k=0; k<arr.shape[0]; k++)
                    {
                        arr.data[i][k] = arr.data[i][k] - coef *arr.data[j][k];
                        I.data[i][k] = I.data[i][k] - coef * I.data[j][k];
                    }
                }
            }
        }

        clean(&arr, NULL);

        return I;
    }

    ndarray_t norm(ndarray_t *this, char *axis) // Calculates only Euclidean distance
    {
        isnull(this);
        double temp=0;

        if(strcmp(axis, "x")==0)
        {
            ndarray_t result = array(this->shape[0],1);

           for(size_t i=0; i<this->shape[0]; i++)
            {
                for(size_t j=0; j<this->shape[1]; j++)
                {        
                    temp += pow(this->data[i][j], 2);
                }

                result.data[i][0] = sqrt(temp);
                
                temp = 0;
            }

            return result;
        }
        else if(strcmp(axis, "y")==0)
        {
            ndarray_t result = array(1, this->shape[1]);

            for(size_t i=0; i<this->shape[1]; i++)
            {
                for(size_t j=0; j<this->shape[0]; j++)
                {        
                    temp += pow(this->data[j][i], 2);
                }

             
                result.data[0][i] = sqrt(temp);

                temp = 0; 
            }

            return result;
        }
        else if(strcmp(axis, "all")==0)
        {
            ndarray_t result = array(1, 1);
            for(size_t i=0; i<this->shape[0]; i++)
            {
                for(size_t j=0; j<this->shape[1]; j++)
                {        
                    temp += pow(this->data[i][j], 2);
                }
            }

            result.data[0][0] = sqrt(temp);


            return result;
        }
        else
        {
            axis_error(axis);
            clean(this, NULL);
            exit(1);
        }

    }

    double det(ndarray_t *this) 
    {
        issquare(this);
        double determinant = 1.0;

        ndarray_t arr = array(this->shape[0], this->shape[1]);
        arr = copy(this);

        for (size_t j = 0; j < arr.shape[0]; j++) 
        {
            size_t maxRow = j;
            double maxVal = arr.data[j][j];

            // Find the maximum absolute value element in column j from rows j to n
            for (size_t i = j + 1; i < arr.shape[0]; i++) {
                if (arr.data[i][j] > maxVal) {
                    maxVal = arr.data[i][j];
                    maxRow = i;
                }
            }

            // Swap the row with maxVal with the current row
            if (maxRow != j) {
                for (size_t k = 0; k < arr.shape[0]; k++) {
                    double temp = arr.data[j][k];
                    arr.data[j][k] = arr.data[maxRow][k];
                    arr.data[maxRow][k] = temp;
                }
                // Multiply the determinant by -1 due to row swap
                determinant *= -1;
            }

            // Divide the current row by the value of A[j][j] to make the leading coefficient 1
            double pivot = arr.data[j][j];
            for (size_t k = 0; k < arr.shape[0]; k++) {
                arr.data[j][k] /= pivot;
            }
            determinant *= pivot;

            // Eliminate the jth column element in other rows
            for (size_t i = j + 1; i < arr.shape[0]; i++) {
                double factor = arr.data[i][j];
                for (size_t k = 0; k < arr.shape[0]; k++) {
                    arr.data[i][k] -= factor * arr.data[j][k];
                }
            }
        }

        // Multiply the determinant by the diagonal elements of the row-echelon form
        for (size_t i = 0; i < arr.shape[0]; i++) {
            determinant *= arr.data[i][i];
        }

        clean(&arr, NULL);
        
        return determinant;
    }


    #pragma GCC optimize("O3", "unroll-loops")
    void qr(ndarray_t *this, ndarray_t *Q, ndarray_t *R) {
        // Initialize Q and R
        *Q = zeros(this->shape[0], this->shape[1]);
        *R = zeros(this->shape[1], this->shape[1]);
        
        // Create working copy
        ndarray_t V = copy(this);
        size_t n = V.shape[1];
        
        // Pre-allocate temporary arrays to avoid repeated allocations
        ndarray_t v = zeros(this->shape[0], 1);
        ndarray_t a = zeros(this->shape[0], 1);
        ndarray_t b = zeros(this->shape[0], 1);
        ndarray_t c = zeros(this->shape[0], 1);
        ndarray_t div_r = zeros(this->shape[0], 1);
    
        for(size_t i=0; i<n; i++) {
            // Copy column i to v instead of creating new array
            for(size_t k=0; k<V.shape[0]; k++) {
                v.data[k][0] = V.data[k][i];
            }
            
            // Calculate norm directly to avoid temporary ndarray_t
            double norm_val = 0.0;
            for(size_t k=0; k<v.shape[0]; k++) {
                norm_val += v.data[k][0] * v.data[k][0];
            }
            R->data[i][i] = sqrt(norm_val);
            
            // Calculate Q[:, i] = v / R[i,i]
            double r_inv = 1.0 / R->data[i][i];
            for(size_t k=0; k<v.shape[0]; k++) {
                Q->data[k][i] = v.data[k][0] * r_inv;
            }
            
            // Update remaining columns
            #pragma GCC unroll 4
            for(size_t j=i+1; j<n; j++) {
                // Calculate dot product directly
                double dot_val = 0.0;
                for(size_t k=0; k<this->shape[0]; k++) {
                    dot_val += Q->data[k][i] * V.data[k][j];
                }
                R->data[i][j] = dot_val;
                
                // Update V[:, j]
                for(size_t k=0; k<V.shape[0]; k++) {
                    V.data[k][j] -= Q->data[k][i] * dot_val;
                }
            }
        }
        
        // Clean up temporary arrays
        clean(&v, NULL);
        clean(&a, NULL);
        clean(&b, NULL);
        clean(&c, NULL);
        clean(&div_r, NULL);
        clean(&V, NULL);
    }

    #pragma GCC optimize("O3", "unroll-loops")
    ndarray_t matmul(ndarray_t *this, ndarray_t *arrayB)
    {
        isnull(this);
        isnull(arrayB);

        ndarray_t result  = {0};
        if(this->shape[1] == arrayB->shape[0])
        {
            result = array(this->shape[1], this->shape[0]);
            for(int i = 0; i<(int)this->shape[0]; i++)
                {
                    for(int j=0; j<(int)this->shape[1]; j++)
                    {
                         result.data[i][j] = 0;
                        for(int k = 0; k<(int)this->shape[0]; k++)
                        {
                            result.data[i][j] += this->data[i][k] * arrayB->data[k][j];
                        }
                    }
                }
            return result;
        }
        
        else
        {
            fprintf(stderr, "Invalid dimensions %ldx%ld and %ldx%ld for array multiplication\n", this->shape[0], this->shape[1], arrayB->shape[0], arrayB->shape[1]);
            perror("Use valid ndarray_t dimesions please\n");
            clean(this, NULL);
            clean(arrayB, NULL);
            exit(1);
        }
    }

  


    #pragma GCC optimize("O3", "unroll-loops")
    ndarray_t outer(ndarray_t* a, ndarray_t* b) 
    {
        
        ndarray_t result = array(a->shape[0], b->shape[0]);

        
        // Compute the outer product
        for (size_t i = 0; i < a->shape[0]; i++) 
        {
            for (size_t j = 0; j < b->shape[0]; j++) {
                result.data[i][j] = a->data[i][0] * b->data[j][0];
            }
        }
        return result;
    }

    #pragma GCC optimize("O3", "unroll-loops")
    ndarray_t dot(ndarray_t* a, ndarray_t* b) 
    {
        
        ndarray_t result = array(1, 1);
        result.data[0][0] = 0;
        
        // Compute the outer product
        for (size_t i = 0; i < a->shape[0]; i++) 
        {
            result.data[0][0] += a->data[i][0] * b->data[i][0];
        }
        return result;
    }

    #pragma GCC optimize("O3", "unroll-loops")
    ndarray_t eig(ndarray_t *this, size_t niters)
    {
        isnull(this);
        issquare(this);
        
        const size_t n = this->shape[0];
        ndarray_t Q = zeros(n, n);
        ndarray_t R = zeros(n, n);
        ndarray_t QQ = identity(n, n);
        ndarray_t Ik = identity(n, n);
        ndarray_t arr = copy(this);
        ndarray_t temp = zeros(n, n);  // Pre-allocate temporary matrix
        
        double convergence_threshold = 1e-10;
        double prev_diag_sum = 0;
        
        for(size_t k = 0; k < niters; k++)
        {
            double Sk = arr.data[0][0];
            
            // In-place scaling of identity matrix
            #pragma GCC unroll 4
            for(size_t i = 0; i < n; i++) {
                Ik.data[i][i] = Sk;
            }
            
            // Subtract Ik from arr in-place
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    if(i == j) arr.data[i][j] -= Ik.data[i][j];
                }
            }
            
            qr(&arr, &Q, &R);
            
            // Optimized matrix multiplication for arr = R*Q + Ik
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    double sum = 0.0;
                    for(size_t p = 0; p < n; p++) {
                        sum += R.data[i][p] * Q.data[p][j];
                    }
                    arr.data[i][j] = sum + (i == j ? Ik.data[i][j] : 0);
                }
            }
            
            // Check for convergence - diagonal sum convergence
            double diag_sum = 0;
            for(size_t i = 0; i < n; i++) {
                diag_sum += arr.data[i][i];
            }
            
            if(k > 0 && fabs(diag_sum - prev_diag_sum) < convergence_threshold) {
                break;  // Convergence reached
            }
            prev_diag_sum = diag_sum;
            
            // Update QQ = QQ * Q more efficiently
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    double sum = 0.0;
                    for(size_t p = 0; p < n; p++) {
                        sum += QQ.data[i][p] * Q.data[p][j];
                    }
                    temp.data[i][j] = sum;
                }
            }
            
            // Copy temp to QQ
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    QQ.data[i][j] = temp.data[i][j];
                }
            }
        }
        
        // Extract eigenvalues from diagonal
        ndarray_t result = array(1, n);
        for(size_t i = 0; i < n; i++) {
            result.data[0][i] = arr.data[i][i];
        }
        
        clean(&arr, NULL);
        clean(&Q, NULL);
        clean(&R, NULL);
        clean(&Ik, NULL);
        clean(&QQ, NULL);
        clean(&temp, NULL);
        
        return result;
    }



    #pragma GCC optimize("O3", "unroll-loops", "fast-math")
    ndarray_t svd(ndarray_t *this)
    {
        // For A = U*S*V^T, we compute singular values by finding eigenvalues of A^T*A
        size_t m = this->shape[0];
        size_t n = this->shape[1];
        
        // Compute A^T*A more efficiently
        ndarray_t ATA = zeros(n, n);
        
        // Direct computation of A^T*A without creating transposed matrix
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                double sum = 0.0;
                for(size_t k = 0; k < m; k++) {
                    sum += this->data[k][i] * this->data[k][j];
                }
                ATA.data[i][j] = sum;
            }
        }
        
        // Use optimized eigenvalue solver with fewer iterations when possible
        size_t niters = n < 10 ? 500 : 1000;  // Adjust based on matrix size
        ndarray_t eigenvalues = eig(&ATA, niters);
        
        // Compute singular values (sqrt of eigenvalues)
        for(size_t i = 0; i < n; i++) {
            // Use fast approximation if available, or precise sqrt
            eigenvalues.data[0][i] = sqrt(fabs(eigenvalues.data[0][i]));
        }
        
        clean(&ATA, NULL);
        
        return eigenvalues;
    }






