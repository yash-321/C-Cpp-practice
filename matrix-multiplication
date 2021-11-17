#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

void fill_matrix(int** matrix, int rows, int cols);
void print_matrix(int** matrix, int rows, int cols);
void multiply_matrices(int** matrix1, int** matrix2, int** result, int m, int n);
void free_matrix(int** matrix, int rows, int cols);
bool isNumber(char number[]);

int main(int argc, char *argv[]){
    int **matrix1; int **matrix2; int **result; int i;

    // Check we have right number of arguments
    if (argc != 4){
        printf("Wrong number of arguments provided!\n");
        printf("Please use this format: ./mat-mult <M> <N> <seed>\n");
        return -1;
    }

    // Valid argument numbers check
    if (!isNumber(argv[1]) || !isNumber(argv[2]) || !isNumber(argv[3])){
        printf("One of the arguments is invalid!\n");
        printf("Please try again!\n");
        return -1;
    }

    // All arguments should convert to integers
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int seed = atoi(argv[3]);

    // Check if either value is 0
    if (m==0 || n==0){
        printf("Value for row or column cannot be 0!\n");
        return -1;
    }

    // Initialize the random number generator with the seed
    srand(seed);

    // Create the 3 matrices
    matrix1 = (int**) malloc(m*sizeof(int*));
    for(i=0;i<m;i++)
        matrix1[i] = (int*) malloc(n*sizeof(int));

    matrix2 = (int**) malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
        matrix2[i] = (int*) malloc(m*sizeof(int));

    result = (int**) malloc(m*sizeof(int*));
    for(i=0;i<m;i++)
        result[i] = (int*) malloc(m*sizeof(int));

    // Fill both matrices with values
    fill_matrix(matrix1, m, n);
    fill_matrix(matrix2, n, m);

    // Print matrices
    printf("MATRIX 1:\n");
    print_matrix(matrix1, m, n);
    printf("MATRIX 2:\n");
    print_matrix(matrix2, n, m);

    // Time function execution time
    clock_t begin = clock();

    multiply_matrices(matrix1, matrix2, result, m, n);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // Display result and execution time
    printf("RESULT:\n");
    print_matrix(result, m, m);
    printf("EXECUTION TIME: %f\n", time_spent);

    // Free memory before ending programme
    free_matrix(matrix1, m, n);
    free_matrix(matrix2, n, m);
    free_matrix(result, m, m);

    return 0;
}

void fill_matrix(int** matrix, int rows, int cols){
    int i; int j;
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)
            matrix[i][j] = rand() % 100;
}

void print_matrix(int** matrix, int rows, int cols){
    int i; int j;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void multiply_matrices(int** matrix1, int** matrix2, int** result, int m, int n){
    int i; int j; int k;
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
                result[i][j]=0;
                for(k=0;k<n;k++)
                    result[i][j]+= matrix1[i][k]*matrix2[k][j];
        }
    }
}

void free_matrix(int** matrix, int rows, int cols){
    int i;
    for (i=0; i<rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}

bool isNumber(char number[]){
    int i;

    // negative number check
    if (number[0] == '-'){
        printf("Negative numbers aren't valid!\n");
        return false;
    }
    for (i=0;number[i]!=0;i++){
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i])){
            printf("Not a valid integer!\n");
            return false;
        }
    }
    return true;
}
