#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Block size for blocked matrix multiplication
// Optimal size depends on CPU cache (typically 32-64)
#define BLOCK_SIZE 32

// Matrix structure definition
typedef struct {
    int rows;
    int cols;
    double* data;
} Matrix;

// Create a matrix with specified dimensions
Matrix* create_matrix(int rows, int cols) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (mat == NULL) {
        printf("Failed to allocate memory for matrix structure\n");
        return NULL;
    }
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)malloc(rows * cols * sizeof(double));
    if (mat->data == NULL) {
        printf("Failed to allocate memory for matrix data\n");
        free(mat);
        return NULL;
    }
    return mat;
}

// Free matrix memory
void free_matrix(Matrix* mat) {
    if (mat != NULL) {
        if (mat->data != NULL) {
            free(mat->data);
        }
        free(mat);
    }
}

// Initialize matrix with random values
void init_matrix_random(Matrix* mat) {
    srand(time(NULL));
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        mat->data[i] = (double)(rand() % 100) / 10.0;
    }
}

// Initialize matrix with fixed values
void init_matrix_fixed(Matrix* mat, double value) {
    for (int i = 0; i < mat->rows * mat->cols; i++) {
        mat->data[i] = value;
    }
}

// Print matrix content (only for small matrices)
void print_matrix(const Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%8.2f ", mat->data[i * mat->cols + j]);
        }
        printf("\n");
    }
}

// Get current time in milliseconds
double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

// Matrix multiplication using i-j-k loop order
Matrix* matrix_multiply_ijk(const Matrix* A, const Matrix* B) {
    if (A->cols != B->rows) {
        printf("Error: Matrix dimensions mismatch!\n");
        return NULL;
    }

    Matrix* C = create_matrix(A->rows, B->cols);
    if (C == NULL) return NULL;

    // Initialize to zero
    for (int i = 0; i < C->rows * C->cols; i++) {
        C->data[i] = 0.0;
    }

    // i-j-k loop order
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            for (int k = 0; k < A->cols; k++) {
                C->data[i * C->cols + j] +=
                    A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }
    }

    return C;
}

// Matrix multiplication using k-i-j loop order
Matrix* matrix_multiply_kij(const Matrix* A, const Matrix* B) {
    if (A->cols != B->rows) {
        printf("Error: Matrix dimensions mismatch!\n");
        return NULL;
    }

    Matrix* C = create_matrix(A->rows, B->cols);
    if (C == NULL) return NULL;

    // Initialize to zero
    for (int i = 0; i < C->rows * C->cols; i++) {
        C->data[i] = 0.0;
    }

    // k-i-j loop order
    for (int k = 0; k < A->cols; k++) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->cols; j++) {
                C->data[i * C->cols + j] +=
                    A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }
    }

    return C;
}

// Matrix multiplication using j-k-i loop order
Matrix* matrix_multiply_jki(const Matrix* A, const Matrix* B) {
    if (A->cols != B->rows) {
        printf("Error: Matrix dimensions mismatch!\n");
        return NULL;
    }

    Matrix* C = create_matrix(A->rows, B->cols);
    if (C == NULL) return NULL;

    // Initialize to zero
    for (int i = 0; i < C->rows * C->cols; i++) {
        C->data[i] = 0.0;
    }

    // j-k-i loop order
    for (int j = 0; j < B->cols; j++) {
        for (int k = 0; k < A->cols; k++) {
            for (int i = 0; i < A->rows; i++) {
                C->data[i * C->cols + j] +=
                    A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }
    }

    return C;
}

// Blocked matrix multiplication for better cache utilization
Matrix* matrix_multiply_blocked(const Matrix* A, const Matrix* B) {
    if (A->cols != B->rows) {
        printf("Error: Matrix dimensions mismatch!\n");
        return NULL;
    }

    Matrix* C = create_matrix(A->rows, B->cols);
    if (C == NULL) return NULL;

    // Initialize to zero
    for (int i = 0; i < C->rows * C->cols; i++) {
        C->data[i] = 0.0;
    }

    // Blocked matrix multiplication
    // Outer loops iterate over blocks
    for (int ii = 0; ii < A->rows; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < B->cols; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < A->cols; kk += BLOCK_SIZE) {
                // Inner loops iterate within each block
                int i_end = (ii + BLOCK_SIZE) < A->rows ? (ii + BLOCK_SIZE) : A->rows;
                int j_end = (jj + BLOCK_SIZE) < B->cols ? (jj + BLOCK_SIZE) : B->cols;
                int k_end = (kk + BLOCK_SIZE) < A->cols ? (kk + BLOCK_SIZE) : A->cols;

                for (int i = ii; i < i_end; i++) {
                    for (int k = kk; k < k_end; k++) {
                        for (int j = jj; j < j_end; j++) {
                            C->data[i * C->cols + j] +=
                                A->data[i * A->cols + k] * B->data[k * B->cols + j];
                        }
                    }
                }
            }
        }
    }

    return C;
}

// Test matrix multiplication with timing
void test_multiplication(const char* name, Matrix* (*multiply_func)(const Matrix*, const Matrix*),
                         Matrix* A, Matrix* B) {
    printf("\nTesting %s...\n", name);

    double start_time = get_time_ms();
    Matrix* C = multiply_func(A, B);
    double end_time = get_time_ms();

    if (C != NULL) {
        printf("Time: %.2f ms\n", end_time - start_time);
        free_matrix(C);
    } else {
        printf("Multiplication failed!\n");
    }
}

int main() {
    const int SIZE = 2000;

    printf("Creating %dx%d matrices...\n", SIZE, SIZE);
    printf("Memory required per matrix: %.2f MB\n", (double)(SIZE * SIZE * sizeof(double)) / (1024 * 1024));

    double start_time = get_time_ms();

    // Create large matrices
    Matrix* A = create_matrix(SIZE, SIZE);
    if (A == NULL) {
        printf("Failed to create matrix A\n");
        return 1;
    }

    Matrix* B = create_matrix(SIZE, SIZE);
    if (B == NULL) {
        printf("Failed to create matrix B\n");
        free_matrix(A);
        return 1;
    }

    double init_time = get_time_ms();

    // Initialize matrices with fixed values for consistency
    printf("Initializing matrices...\n");
    init_matrix_fixed(A, 1.0);
    init_matrix_fixed(B, 2.0);

    double ready_time = get_time_ms();
    printf("Initialization time: %.2f ms\n", ready_time - init_time);
    printf("Total preparation time: %.2f ms\n", ready_time - start_time);

    // Test different loop orders
    printf("\n========================================");
    printf("\nMatrix Multiplication Performance Test");
    printf("\nMatrix size: %dx%d", SIZE, SIZE);
    printf("\n========================================");

    // *! time consuming process
    test_multiplication("i-j-k loop order", matrix_multiply_ijk, A, B);
    test_multiplication("k-i-j loop order", matrix_multiply_kij, A, B);
    test_multiplication("j-k-i loop order", matrix_multiply_jki, A, B);
    test_multiplication("Blocked multiplication", matrix_multiply_blocked, A, B);

    printf("\n========================================\n");

    // Clean up
    printf("Cleaning up memory...\n");
    free_matrix(A);
    free_matrix(B);

    printf("Test completed!\n");

    return 0;
}
