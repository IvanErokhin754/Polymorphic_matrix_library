#include "Matrix.h"
#include "FieldInfo.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void PrintMatrix(const Matrix *matrix)
{
    if (!matrix || !matrix->size || !matrix->data || !matrix->field || !matrix->field->print) return;

    size_t matrix_size = matrix->size;
    size_t field_size = matrix->field->size;

    for (size_t i = 0; i < matrix_size; i++){
        for (size_t j = 0; j < matrix_size; j++){
            const void *elem = matrix->data + (i * matrix_size + j) * field_size;
            matrix->field->print(elem); 
            if (j + 1 < matrix_size) printf(" ");
        }
        printf("\n");
    }
}


Matrix* CreateMatrix(size_t size, const FieldInfo *field)
{
    if (size == 0 || field == NULL || field->size == 0)
        return NULL;
    if (size > SIZE_MAX / size) return NULL;

    size_t count = size * size;
    Matrix* m = malloc(sizeof(*m));

    if (!m) return NULL;

    m->field = field;
    m->size = size;

    if (field->size > SIZE_MAX / count){
        free(m);   
        return NULL;
    }
    m->data = malloc(count * field->size);

    if (!m->data){
        free(m);
        return NULL;
    }

    for (size_t i = 0; i < count; i++){
        field->zero(m->data + i * field->size);
    }
  
    return m;
}


void DestroyMatrix(Matrix *matrix)
{
    if (!matrix) return;
    free(matrix->data);
    matrix->data = NULL;
    free(matrix);
}


int SetMatrix(Matrix *matrix, const size_t i, const size_t j, const void *value)
{
    if (!matrix || i >= matrix->size || j >= matrix->size) return 1;
    if (!matrix->data || !matrix->field || !value) return 1;
    const size_t element_index = i * matrix->size + j;
    unsigned char *dst = matrix->data + element_index * matrix->field->size;
    memcpy(dst, value, matrix->field->size);

    return 0;
}


void GetMatrix(const Matrix *matrix, const size_t i, const size_t j, void *out)
{
    if (!matrix || i >= matrix->size || j >= matrix->size) return;
    if (!matrix->data || !matrix->field) return;
    if (!out) return;
    const size_t element_index = i * matrix->size + j;
    const unsigned char *src = matrix->data + element_index * matrix->field->size;
    memcpy(out, src, matrix->field->size);
}


int MatrixAdd(const Matrix *matrix1, const Matrix *matrix2, Matrix *out){
    if (!(matrix1 && matrix2 && out)) return 1;
    if (!(matrix1->data && matrix2->data && out->data)) return 1;
    if (!(matrix1->field && matrix2->field && out->field)) return 1;

    if (matrix1->size != matrix2->size) return 1;
    if (matrix1->size != out->size) return 1;
    if ((matrix1->field != matrix2->field) || (matrix1->field != out->field)) return 1;
    
    size_t count = matrix1->size * matrix1->size;
    size_t field_size = matrix1->field->size;
    for (size_t element_matrix = 0; element_matrix < count; element_matrix++){
        unsigned char *dst = out->data + element_matrix * field_size;
        const void *element1 = matrix1->data + element_matrix * field_size;
        const void *element2 = matrix2->data + element_matrix * field_size;

        out->field->add(dst, element1, element2);
    }
    return 0;
}


int MatrixMultiply(const Matrix *matrix1, const Matrix *matrix2, Matrix *out){
    if (!(matrix1 && matrix2 && out)) return 1; 
    if (!(matrix1->data && matrix2->data && out->data)) return 1;
    if (!(matrix1->field && matrix2->field && out->field)) return 1;

    if (matrix1->size != matrix2->size) return 1;
    if (matrix1->size != out->size) return 1;
    if ((matrix1->field != matrix2->field) || (matrix1->field != out->field)) return 1;
    size_t matrix_size = matrix1->size;
    size_t field_size = matrix1->field->size;

    unsigned char *sum = malloc(field_size);
    unsigned char *temp = malloc(field_size);
    if (!sum || !temp){
        free(sum);
        free(temp);
        return 1;
    }

    for (size_t i = 0; i < matrix_size; i++){
        for (size_t j = 0; j < matrix_size; j++){
            out->field->zero(sum);
            for (size_t k = 0; k < matrix_size; k++){
                const void *elementAik = matrix1->data + (i * matrix_size + k) * field_size;
                const void *elementAkj = matrix2->data + (k * matrix_size + j) * field_size; 

                out->field->multiply(temp, elementAik, elementAkj);
                out->field->add(sum, sum, temp);

            }
            void *element_out = out->data + (i * matrix_size + j) * field_size;
            memcpy(element_out, sum, field_size);
        }
        
    }
    free(sum);
    free(temp);
    return 0;
}


int ScalarMultiply(Matrix *matrix, const FieldInfo *scalar_field, const void *scalar){
    if (!matrix || !scalar) return 1;
    if (!matrix->data) return 1;
    if (!matrix->field || !scalar_field) return 1;
    if (matrix->field != scalar_field) return 1;
    size_t matrix_size = matrix->size * matrix->size;
    size_t field_size = matrix->field->size;
    unsigned char *temp = malloc(field_size);
    if (!temp) return 1;
    for (size_t i = 0; i < matrix_size; i++){
        void *element = matrix->data + i * field_size;
        matrix->field->multiply(temp, element, scalar);
        memcpy(element, temp, field_size);
    }

    free(temp);
    return 0;
}   


int AddLinearCombination(Matrix *matrix, size_t row_i, const void *combination){
    if (!matrix || !combination) return 1;
    if (!matrix->data) return 1;
    if (!matrix->field) return 1;
    if (row_i >= matrix->size) return 1;
    size_t matrix_size = matrix->size;
    size_t field_size = matrix->field->size;
    unsigned char *temp, *sum;

    temp = malloc(field_size); sum = malloc(field_size);
    if (!temp || !sum){
        free(temp);
        free(sum);
        return 1;
    }

    const unsigned char *coeffs = (const unsigned char*)combination;

    for (size_t j = 0; j < matrix_size; j++){
        matrix->field->zero(sum);
        for (size_t k = 0; k < matrix_size; k++){
            if (k == row_i) continue;

            const void *coeff_k = coeffs + k * field_size;
            const void *matrix_kj = matrix->data + (k * matrix_size + j) * field_size;

            matrix->field->multiply(temp, coeff_k, matrix_kj);
            matrix->field->add(sum, sum, temp);
        }
        void *matrix_ij = matrix->data + (row_i * matrix_size + j) * field_size;
        matrix->field->add(matrix_ij, matrix_ij, sum);
    }

    free(temp); free(sum);
    return 0;
}