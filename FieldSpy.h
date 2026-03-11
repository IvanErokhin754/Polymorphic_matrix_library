#ifndef FIELD_SPY_H
#define FIELD_SPY_H

#include "FieldInfo.h"

const FieldInfo *FieldSpy(const FieldInfo *real);

void spy_reset(void);
int spy_zero_calls(void);
int spy_add_calls(void);
int spy_multiply_calls(void);
int spy_print_calls(void);


#endif /* FIELD_SPY_H */
