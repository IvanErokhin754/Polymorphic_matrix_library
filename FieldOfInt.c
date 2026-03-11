#include <stdio.h>
#include "FieldInfo.h"

static void int_zero(void *null_target)
{
    *(int*)null_target = 0;
}

static void int_add(void *res, const void *target1, const void *target2)
{
    *(int*)res = *(const int*)target1 + *(const int*)target2;
}

static void int_multiply(void *res, const void *target1, const void *target2)
{
    *(int*)res = (*(const int*)target1) * (*(const int*)target2);
}

static void int_print(const void *integer_target)
{
    printf("%d", *(const int*)integer_target);
}

static int int_read(void *element)
{
    return scanf("%d", (int*)element) != 1;
}

const FieldInfo *OfInt(void)
{
    static FieldInfo f;
    static int initialized = 0;
    if (!initialized){
        f.size = sizeof(int);
        f.zero = int_zero;
        f.add = int_add;
        f.multiply = int_multiply;
        f.print = int_print;
        f.read = int_read;
        initialized = 1;
    }
    return &f;
}
