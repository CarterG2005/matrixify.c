// Carter Gerlach

#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
int main(int argc, char** argv);
int *createOneDimensionalArray(int size);
int **createMatrix(int rows, int columns);
int readFile(char *fileName);
int **addMatrices(int **defaultMatrix, int **readInMatrix, int rows, int cols);
int computeDiagonalSum(int **matrix, int rows, int cols);
void collectBytes(int **matrix, int rows, int columns);

// The main function
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Call the readFile function and pass the file name from argv
    readFile(argv[1]);

    // Return zero as required 
    return 0;
}

// Function to create a 1D array
int *createOneDimensionalArray(int size) {
    int* array = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = 1;
    }
    printf("Array of size %d is created.\n", size);
    return array;
}

// Function to create a 2D matrix 
int **createMatrix(int rows, int columns) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(columns * sizeof(int));
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 1;
        }
    }
    printf("Matrix of size (%d, %d) is created.\n", rows, columns);
    return matrix;
}

// Function to read file and extract matrix information
int readFile(char *fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Failed to open file: %s\n", fileName);
        return 0;
    }

    int rows1, cols1, rows2, cols2;

    // Read dimensions for the first matrix
    fscanf(file, "%d %d", &rows1, &cols1);
    printf("Matrix of size (%d, %d) is found.\n", rows1, cols1);

    // Create the first matrix
    int **matrix1 = createMatrix(rows1, cols1);
    int *OneDimensionalArray = createOneDimensionalArray(rows1);

    // Read dimensions for the second matrix
    fscanf(file, "%d %d", &rows2, &cols2);
    printf("Matrix of size (%d, %d) is found.\n", rows2, cols2);

    // Create the second matrix
    int **matrix2 = createMatrix(rows2, cols2);
    for (int i = 0; i < rows2; i++) {
         matrix2[i] = (int*)malloc(cols2 * sizeof(int));
        for (int j = 0; j < cols2; j++){
            fscanf(file, "%d", &matrix2[i][j]);
        }
    }

    // Ensure the matrices are compatible for addition
    if (rows1 == rows2 && cols1 == cols2) {
        // Call the addMatrices function to add matrix1 and matrix2
        int **resultMatrix = addMatrices(matrix1, matrix2, rows1, cols1);
        // Call computeDiagonalSum to calculate the diagonal sum of the result matrix
        computeDiagonalSum(resultMatrix, rows1, cols1);
        collectBytes(resultMatrix, rows1, cols1);
        
        // Free the result matrix after use
        for (int i = 0; i < rows1; i++) {
            free(resultMatrix[i]);
        }
        free(resultMatrix);
    } else {
        printf("Matrices are not of the same size. Cannot add.\n");
        printf("Matrices were not able to be added together\n");
    } 

    // Free the dynamically allocated memory
    for (int i = 0; i < rows1; i++) free(matrix1[i]);
    free(matrix1);
    for (int i = 0; i < rows2; i++) free(matrix2[i]);
    free(matrix2);

    // Close the file
    fclose(file);

    return 4; // difficulty level 
}

// Function to add two matrices
int **addMatrices(int** defaultMatrix, int** readInMatrix, int rows, int cols) {
    if (!defaultMatrix || !readInMatrix) {
        printf("One or both matrices are NULL. Cannot add.\n");
        return NULL;
    }

    int **resultMatrix = createMatrix(rows, cols);
    if (!resultMatrix) {
        printf("Memory allocation for result matrix failed.\n");
        return NULL;
    }

    // Perform the addition
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            resultMatrix[i][j] = defaultMatrix[i][j] + readInMatrix[i][j];
        }
    }

    // Print the result
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    return resultMatrix;
}

// Function to compute the sum of the main diagonal of a matrix
int computeDiagonalSum(int **matrix, int rows, int cols) {
    // Check if the matrix is square
    if (rows != cols) {
        printf("Matrix is not square. Cannot compute diagonal sum.\n");
        return 4; // Difficulty level
    }

    int diagonalSum = 0;
    for (int i = 0; i < rows; i++) {
        diagonalSum += matrix[i][i];
    }

    printf("Diagonal Sum is: %d\n", diagonalSum);
    return 4; // Difficulty rating for this function
}

void collectBytes(int **matrix, int rows, int columns) {
    int bytes = rows * columns * sizeof(int);
    printf("Total bytes of matrix: %d\n", bytes);
    printf("In use at exit %d bytes in %d blocks\n", bytes, bytes);
    
}
