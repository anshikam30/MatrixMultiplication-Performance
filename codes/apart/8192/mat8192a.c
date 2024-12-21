#include <stdio.h>
#include <stdlib.h>

#define SIZE 8192

int main() {
    int **array1 = malloc(SIZE * sizeof(int *));
    int **array2 = malloc(SIZE * sizeof(int *));
    int **result = malloc(SIZE * sizeof(int *));

    for (int i = 0; i < SIZE; i++) {
        array1[i] = malloc(SIZE * sizeof(int));
        array2[i] = malloc(SIZE * sizeof(int));
        result[i] = malloc(SIZE * sizeof(int));
    }

    // Initialize both matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array1[i][j] = (int) rand();
            array2[i][j] = (int) rand(); 
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication: result = array1 * array2
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
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
    for (int i = 0; i < SIZE; i++) {
        free(array1[i]);
        free(array2[i]);
        free(result[i]);
    }
    free(array1);
    free(array2);
    free(result);

    return 0;
}

