#include <stdio.h>
#include <stdlib.h>
#include "UI.h"
#include "FieldInfo.h"
#include "FieldOfInt.h"
#include "FieldOfDouble.h"
#include "Matrix.h"

void ui(void)
{
    int tmp_command = 0;
    int start_end = 1;
    int i = 0, j = 0;
    int size = 0;

    static Matrix *matrix1 = NULL;
    static Matrix *matrix2 = NULL;
    static Matrix *out = NULL;
    Matrix *tmp_matrix = NULL;

    int command = 0;
    static const FieldInfo *field = NULL;

    while (start_end) {
        printf("\n");
        printf("1) Choose field (int/double)\n");
        printf("2) Create(recreate) matrix1 (N)\n");
        printf("3) Create(recreate) matrix2 (N)\n");
        printf("4) Set element in matrix\n");
        printf("5) Print Matrix\n");
        printf("6) Add Matrices: C = A + B\n");
        printf("7) Multiply Matrices: C = A * B\n");
        printf("8) Scalar Multiply\n");
        printf("9) Add Linear Combination\n");
        printf("0) Exit\n");

        printf("Enter command: ");
        if (scanf("%d", &command) != 1) {
            printf("\nInput ERROR!\n");
            return;
        }

        if (command == 1) { // Choose field
            printf("1) Int\n2) Double\n");
            printf("Choose field: ");
            if (scanf("%d", &tmp_command) != 1) return;

            if (tmp_command == 1) {
                field = OfInt();
            }
            else if (tmp_command == 2) {
                field = OfDouble();
            }
            else {
                printf("Wrong number!\n");
                continue;
            }

            DestroyMatrix(matrix1);
            DestroyMatrix(matrix2);
            DestroyMatrix(out);
            matrix1 = matrix2 = out = tmp_matrix = NULL;

            printf("Field was chosen successfully!\n");
        }


        else if (command == 2) { // Create Matrix1
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Size of Matrix1: ");
            if (scanf("%d", &size) != 1) return;

            if (size <= 0) {
                printf("Wrong size!\n");
                continue;
            }

            DestroyMatrix(matrix1);
            matrix1 = CreateMatrix(size, field);

            DestroyMatrix(out);
            out = NULL;

            if (!matrix1) {
                printf("Failed to create matrix1!\n");
                continue;
            }

            printf("Matrix1 was created successfully!\n");
        }


        else if (command == 3) { // Create Matrix2
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Size of Matrix2: ");
            if (scanf("%d", &size) != 1) return;

            if (size <= 0) {
                printf("Wrong size!\n");
                continue;
            }

            DestroyMatrix(matrix2);
            matrix2 = CreateMatrix(size, field);

            DestroyMatrix(out);
            out = NULL;

            if (!matrix2) {
                printf("Failed to create matrix2!\n");
                continue;
            }

            printf("Matrix2 was created successfully!\n");
        }


        else if (command == 4) { // Set element
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Choose the matrix (1, 2): ");
            if (scanf("%d", &tmp_command) != 1) return;

            if (tmp_command == 1) tmp_matrix = matrix1;
            else if (tmp_command == 2) tmp_matrix = matrix2;
            else {
                printf("Wrong matrix number!\n");
                continue;
            }

            if (!tmp_matrix) {
                printf("You didn't create this matrix!\n");
                continue;
            }

            printf("Enter matrix indices (i, j): ");
            if (scanf("%d%d", &i, &j) != 2) return;

            if (i < 0 || j < 0 || i >= (int)tmp_matrix->size || j >= (int)tmp_matrix->size) {
                printf("Index is larger than matrix size!\n");
                continue;
            }

            void *value = malloc(tmp_matrix->field->size);
            if (!value) {
                printf("Memory allocation failed!\n");
                continue;
            }
            
            printf("Enter value: ");

            if (tmp_matrix->field->read(value) != 0) {
                printf("Input error!\n");
                free(value);
                continue;
            }

            if (SetMatrix(tmp_matrix, i, j, value) != 0) {
                printf("Failed to set element!\n");
            }

            free(value);

            printf("Element was set successfully!\n");
        }


        else if (command == 5) { // Print matrix
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Choose the matrix (1, 2, 3): ");
            if (scanf("%d", &tmp_command) != 1) return;

            if (tmp_command == 1) tmp_matrix = matrix1;
            else if (tmp_command == 2) tmp_matrix = matrix2;
            else if (tmp_command == 3) tmp_matrix = out;
            else {
                printf("Wrong matrix number!\n");
                continue;
            }

            if (!tmp_matrix) {
                printf("You didn't create this matrix!\n");
                continue;
            }

            printf("Matrix:\n");
            PrintMatrix(tmp_matrix);
        }


        else if (command == 6) { // Sum matrix
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            if (!matrix1) {
                printf("First Matrix is not created!\n");
                continue;
            }

            if (!matrix2) {
                printf("Second Matrix is not created!\n");
                continue;
            }

            if (matrix1->size != matrix2->size) {
                printf("Matrices have different sizes!\n");
                continue;
            }

            if (!out) {
                out = CreateMatrix(matrix1->size, matrix1->field);
                if (!out) {
                    printf("Failed to create output matrix!\n");
                    continue;
                }
            }

            if (MatrixAdd(matrix1, matrix2, out) != 0) {
                printf("Addition failed!\n");
                continue;
            }

            printf("Result was written to output matrix!\n");
        }


        else if (command == 7) { // Mult matrix
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            if (!matrix1) {
                printf("First Matrix is not created!\n");
                continue;
            }

            if (!matrix2) {
                printf("Second Matrix is not created!\n");
                continue;
            }

            if (matrix1->size != matrix2->size) {
                printf("Matrices have different sizes!\n");
                continue;
            }

            if (!out) {
                out = CreateMatrix(matrix1->size, matrix1->field);
                if (!out) {
                    printf("Failed to create output matrix!\n");
                    continue;
                }
            }

            if (MatrixMultiply(matrix1, matrix2, out) != 0) {
                printf("Multiplication failed!\n");
                continue;
            }

            printf("Result was written to output matrix!\n");
        }


        else if (command == 8) { // Scalar Multiply
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Choose the matrix (1, 2, 3): ");
            if (scanf("%d", &tmp_command) != 1) return;

            if (tmp_command == 1) tmp_matrix = matrix1;
            else if (tmp_command == 2) tmp_matrix = matrix2;
            else if (tmp_command == 3) tmp_matrix = out;
            else {
                printf("Wrong matrix number!\n");
                continue;
            }

            if (!tmp_matrix) {
                printf("You didn't create this matrix!\n");
                continue;
            }

            void *scalar = malloc(tmp_matrix->field->size);
            if (!scalar) {
                printf("Memory allocation failed!\n");
                continue;
            }

            printf("Enter scalar: ");
            if (tmp_matrix->field->read(scalar) != 0) {
                printf("Input error!\n");
                free(scalar);
                continue;
            }

            if (ScalarMultiply(tmp_matrix, tmp_matrix->field, scalar) != 0) {
                printf("Scalar multiplication failed!\n");
                free(scalar);
                continue;
            }

            free(scalar);

            printf("Scalar multiplication was successful!\n");
        }


        else if (command == 9) { // Add Linear Combination
            if (!field) {
                printf("You didn't choose the field!\n");
                continue;
            }

            printf("Choose the matrix (1, 2): ");
            if (scanf("%d", &tmp_command) != 1) return;

            if (tmp_command == 1) tmp_matrix = matrix1;
            else if (tmp_command == 2) tmp_matrix = matrix2;
            else {
                printf("Wrong matrix number!\n");
                continue;
            }

            if (!tmp_matrix) {
                printf("You didn't create this matrix!\n");
                continue;
            }

            printf("Enter row index: ");
            if (scanf("%d", &i) != 1) return;

            if (i < 0 || i >= (int)tmp_matrix->size) {
                printf("Wrong row index!\n");
                continue;
            }

            void *combination = malloc(tmp_matrix->size * tmp_matrix->field->size);
            if (!combination) {
                printf("Memory allocation failed!\n");
                continue;
            }

            unsigned char *coeffs = combination;
            printf("Enter %zu coefficients:\n", tmp_matrix->size);

            int input_error = 0;

            for (size_t k = 0; k < tmp_matrix->size; k++) {
                if (tmp_matrix->field->read(coeffs + k * tmp_matrix->field->size) != 0) {
                    printf("Input error!\n");
                    input_error = 1;
                    break;
                }
            }

            if (input_error) {
                free(combination);
                continue;
            }

            if (AddLinearCombination(tmp_matrix, i, combination) != 0) {
                printf("Operation failed!\n");
                free(combination);
                continue;
            }

            free(combination);
            printf("Linear combination was added successfully!\n");
        }


        else if (command == 0) {
            start_end = 0;
        }

        else {
            printf("Wrong number!\n");
        }

    }

    DestroyMatrix(matrix1);
    DestroyMatrix(matrix2);
    DestroyMatrix(out);
}