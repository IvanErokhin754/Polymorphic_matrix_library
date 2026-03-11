#ifndef FIELD_INFO_H
#define FIELD_INFO_H
#include <stddef.h>

typedef struct FieldInfo{
    size_t size;
    void (*zero)(void *null_target);
    void (*add)(void *res, const void *target1, const void *target2); //element - target
    void (*multiply)(void *res, const void *target1, const void *target2);
    void (*print)(const void *target);
    int (*read)(void *element);

} FieldInfo;

#endif /* FIELD_INFO_H */
