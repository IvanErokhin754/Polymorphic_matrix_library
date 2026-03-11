#include <stdio.h>
#include "FieldInfo.h"

static void double_zero(void *null_target)
{
    *(double*)null_target = 0.0;
}

static void double_add(void *result, const void *target1, const void *target2)
{
    *(double*)result = *(const double*)target1 + *(const double*)target2;
}

static void double_multiply(void *result, const void *target1, const void *target2)
{
    *(double*)result = *(const double*)target1 * *(const double*)target2;
}

static void double_print(const void *double_target)
{
    printf("%g", *(const double*)double_target);
}

static int double_read(void *element)
{
    return scanf("%lf", (double*)element) != 1;
}

const FieldInfo *OfDouble(void)
{
    static FieldInfo f;
    static int initialized = 0;
    if (!initialized){
        f.size = sizeof(double);
        f.zero = double_zero;
        f.add = double_add;
        f.multiply = double_multiply;
        f.print = double_print;
        f.read = double_read;
        initialized = 1;
    }
    return &f;
}