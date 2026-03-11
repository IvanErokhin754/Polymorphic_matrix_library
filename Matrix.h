#ifndef MATRIX_H
#define MATRIX_H
#include "FieldInfo.h"
#include <stddef.h>

typedef struct Matrix{
    size_t size; // размер
    const FieldInfo *field; // тип данных
    unsigned char *data; // массив
} Matrix;

void PrintMatrix(const Matrix *matrix);
Matrix *CreateMatrix(size_t size, const FieldInfo *field);
void DestroyMatrix(Matrix *matrix);
int SetMatrix(Matrix *matrix, const size_t i, const size_t j, const void *value);
void GetMatrix(const Matrix *matrix, const size_t i, const size_t j, void *out);
int MatrixAdd(const Matrix *matrix1, const Matrix *matrix2, Matrix *out); 
int MatrixMultiply(const Matrix *matrix1, const Matrix *matrix2, Matrix *out);
int ScalarMultiply(Matrix *matrix, const FieldInfo *scalar_field, const void *scalar);
int AddLinearCombination(Matrix *matrix, size_t row_i, const void *combination);

#endif /* MATRIX_H */
