#include "FieldSpy.h"
#include <stdio.h>
#include <assert.h>

typedef struct FieldSpy{
    const FieldInfo *real;
    int zero_calls;
    int add_calls;
    int multiply_calls;
    int print_calls;
} SpyState;

static SpyState g_spy = {0};

static void spy_zero(void *element)
{
    g_spy.zero_calls++;
    assert(g_spy.real && g_spy.real->zero);
    g_spy.real->zero(element);
}

static void spy_add(void *res, const void *a, const void *b)
{
    g_spy.add_calls++;
    assert(g_spy.real && g_spy.real->add);
    g_spy.real->add(res, a, b);
}

static void spy_multiply(void *res, const void *a, const void *b)
{
    g_spy.multiply_calls++;
    assert(g_spy.real && g_spy.real->multiply);
    g_spy.real->multiply(res, a, b);
}

static void spy_print(const void *element)
{
    g_spy.print_calls++;
    assert(g_spy.real && g_spy.real->print);
    g_spy.real->print(element);
}

static int spy_read(void *element)
{
    assert(g_spy.real && g_spy.real->read);
    return g_spy.real->read(element);
}

void spy_reset(void)
{
    g_spy.zero_calls = 0;
    g_spy.add_calls = 0;
    g_spy.multiply_calls = 0;
    g_spy.print_calls = 0;
}

int spy_zero_calls(void)     {return g_spy.zero_calls;}
int spy_add_calls(void)      {return g_spy.add_calls;}
int spy_multiply_calls(void) {return g_spy.multiply_calls;}
int spy_print_calls(void)    {return g_spy.print_calls;}

const FieldInfo *FieldSpy(const FieldInfo *real)
{
    assert(real);

    g_spy.real = real;

    static FieldInfo spy_field;
    static int initialized = 0;
    
    if (!initialized){
        spy_field.zero = spy_zero;
        spy_field.add = spy_add;
        spy_field.multiply = spy_multiply;
        spy_field.print = spy_print;
        spy_field.read = spy_read;
        initialized = 1;
    }

    spy_field.size = real->size;
    return &spy_field;
}
