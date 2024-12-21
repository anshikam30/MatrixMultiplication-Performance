#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#define SIZE 2048
#define HUGEPAGE_Size (2 * 1024 * 1024)
int **allocate_hugepage_matrix(int rows, int cols)
{
    // Total size needed for the matrix (rows * cols * sizeof(double))
    int matrix_size = rows * cols * sizeof(int);

    // Request huge page memory using mmap()
    void *ptr = mmap(NULL, matrix_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);

    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Allocate an array of double pointers for the 2D matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Point each row of the matrix to the appropriate part of the mmap-ed huge page block
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)((char *)ptr + i * cols * sizeof(int));
    }

    return matrix;
}
// Free the 2D matrix allocated using huge pages
void free_hugepage_matrix(int **matrix, int rows, int cols)
{
    // Calculate the total matrix size
    int matrix_size = rows * cols * sizeof(int);

    // Unmap the huge page memory
    munmap(matrix[0], matrix_size);

    // Free the array of row pointers
    free(matrix);
}
int main()
{
    int **array1 = allocate_hugepage_matrix(SIZE, SIZE);
    int **array2 = allocate_hugepage_matrix(SIZE, SIZE);
    int **result = allocate_hugepage_matrix(SIZE, SIZE);

    // for (int i = 0; i < SIZE; i++) {
    //     array1[i] = malloc(SIZE * sizeof(int));
    //     array2[i] = malloc(SIZE * sizeof(int));
    //     result[i] = malloc(SIZE * sizeof(int));
    // }

    // Initialize both matrices
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            array1[i][j] = (int)rand();
            array2[i][j] = (int)rand();
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication: result = array1 * array2
    for (int k = 0; k < SIZE; k++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                result[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }

    // // Print all values of the result matrix
    // for (int i = 0; i < SIZE; i++) {
    //     for (int j = 0; j < SIZE; j++) {
    //         printf("%d ", result[i][j]);
    //     }
    //     printf("\n"); // New line for each row
    // }

    // Free allocated memory
    // printf("%d\n", array1[0][0]);
    free_hugepage_matrix(array1, SIZE, SIZE);
    free_hugepage_matrix(array2, SIZE, SIZE);
    free_hugepage_matrix(result, SIZE, SIZE);

    return 0;
}
