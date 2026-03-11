#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "Matrix.h"
#include "Tests.h"
#include "FieldOfInt.h"
#include "FieldOfDouble.h"
#include "FieldSpy.h"

static const double eps = 1e-9;

static void test_create_set_get_int(void)
{
    Matrix *m;
    int value;
    //------Good cases------
    m = CreateMatrix(2, OfInt());
    assert(m != NULL);

    value = 2;
    assert(SetMatrix(m, 0, 0, &value) == 0);
    
    value = 1;
    assert(SetMatrix(m, 0, 1, &value) == 0);

    value = 3;
    assert(SetMatrix(m, 1, 0, &value) == 0);

    value = 5;
    assert(SetMatrix(m, 1, 1, &value) == 0);

    value = 0;

    GetMatrix(m, 0, 0, &value);
    assert(value == 2);

    GetMatrix(m, 0, 1, &value);
    assert(value == 1);

    GetMatrix(m, 1, 0, &value);
    assert(value == 3);

    GetMatrix(m, 1, 1, &value);
    assert(value == 5);
    ///////////////////////////

    //-----Bad cases-----
    value = 123456789;

    GetMatrix(m, 2, 2, &value);
    assert(value == 123456789);

    GetMatrix(m, 0, 2, &value);
    assert(value == 123456789);

    GetMatrix(m, 2, 0, &value);
    assert(value == 123456789);

    value = 99;
    assert(SetMatrix(m, 2, 2, &value) == 1);
    assert(SetMatrix(m, 0, 2, &value) == 1);
    assert(SetMatrix(m, 2, 0, &value) == 1);

    ///////////////////////////

    DestroyMatrix(m);
}

static void test_create_set_get_double(void)
{
    Matrix *m;
    double value;
    //------Good cases------
    m = CreateMatrix(2, OfDouble());
    assert(m != NULL);

    value = 123.123;
    assert(SetMatrix(m, 0, 0, &value) == 0);
    
    value = 321.123;
    assert(SetMatrix(m, 0, 1, &value) == 0);

    value = 4151532.45125125;
    assert(SetMatrix(m, 1, 0, &value) == 0);

    value = 97124.99900001;
    assert(SetMatrix(m, 1, 1, &value) == 0);

    value = 0;

    GetMatrix(m, 0, 0, &value);
    assert(fabs(value - 123.123) < eps);

    GetMatrix(m, 0, 1, &value);
    assert(fabs(value - 321.123) < eps);

    GetMatrix(m, 1, 0, &value);
    assert(fabs(value - 4151532.45125125) < eps);

    GetMatrix(m, 1, 1, &value);
    assert(fabs(value - 97124.99900001) < eps);

    /////////////////////////////////



    //-----Bad cases-----
    value = 123456789.0;

    GetMatrix(m, 2, 2, &value);
    assert(fabs(value - 123456789.0) < eps);

    GetMatrix(m, 0, 2, &value);
    assert(fabs(value - 123456789.0) < eps);

    GetMatrix(m, 2, 0, &value);
    assert(fabs(value - 123456789.0) < eps);

    value = 99.0001;
    assert(SetMatrix(m, 2, 2, &value) == 1);
    assert(SetMatrix(m, 0, 2, &value) == 1);
    assert(SetMatrix(m, 2, 0, &value) == 1);

    ///////////////////////////////

    DestroyMatrix(m);

}

static void test_sum_int(void)
{
    Matrix *m1, *m2, *m3;
    m1 = CreateMatrix(2, OfInt()); assert(m1);
    m2 = CreateMatrix(2, OfInt()); assert(m2);
    m3 = CreateMatrix(2, OfInt()); assert(m3);

    int a00 = 1, a01 = 2, a10 = 3, a11 = 4;
    int b00 = 5, b01 = 6, b10 = 7, b11 = 8;
    
    assert(SetMatrix(m1, 0, 0, &a00) == 0);
    assert(SetMatrix(m1, 0, 1, &a01) == 0);
    assert(SetMatrix(m1, 1, 0, &a10) == 0);
    assert(SetMatrix(m1, 1, 1, &a11) == 0);

    assert(SetMatrix(m2, 0, 0, &b00) == 0);
    assert(SetMatrix(m2, 0, 1, &b01) == 0);
    assert(SetMatrix(m2, 1, 0, &b10) == 0);
    assert(SetMatrix(m2, 1, 1, &b11) == 0);

    assert(MatrixAdd(m1, m2, m3) == 0);

    int x;
    GetMatrix(m3, 0, 0, &x); assert(x == 6);
    GetMatrix(m3, 0, 1, &x); assert(x == 8);
    GetMatrix(m3, 1, 0, &x); assert(x == 10);
    GetMatrix(m3, 1, 1, &x); assert(x == 12);


    //-----Bad case-----
    Matrix *m4;
    m4 = CreateMatrix(3, OfInt());
    assert(m4 != NULL);

    assert(MatrixAdd(m1, m3, m4) == 1);
    DestroyMatrix(m4);


    Matrix *md;
    md = CreateMatrix(2, OfDouble());
    assert(md != NULL);

    assert(MatrixAdd(m1, md, m3) == 1);
    DestroyMatrix(md);
    ////////////////////////////////////

    DestroyMatrix(m1); DestroyMatrix(m2); DestroyMatrix(m3);
}

static void test_sum_double(void)
{
    Matrix *m1, *m2, *m3;
    m1 = CreateMatrix(2, OfDouble()); assert(m1);
    m2 = CreateMatrix(2, OfDouble()); assert(m2);
    m3 = CreateMatrix(2, OfDouble()); assert(m3);

    double a00 = 123.123, a01 = 213.1412, a10 = 315.515, a11 = 24124.5150;
    double b00 = 5.7437, b01 = 6.6267, b10 = 7.412, b11 = 84.1245;
    
    assert(SetMatrix(m1, 0, 0, &a00) == 0);
    assert(SetMatrix(m1, 0, 1, &a01) == 0);
    assert(SetMatrix(m1, 1, 0, &a10) == 0);
    assert(SetMatrix(m1, 1, 1, &a11) == 0);

    assert(SetMatrix(m2, 0, 0, &b00) == 0);
    assert(SetMatrix(m2, 0, 1, &b01) == 0);
    assert(SetMatrix(m2, 1, 0, &b10) == 0);
    assert(SetMatrix(m2, 1, 1, &b11) == 0);

    assert(MatrixAdd(m1, m2, m3) == 0);

    double x;
    GetMatrix(m3, 0, 0, &x); assert(fabs(x - 128.866700) < eps);
    GetMatrix(m3, 0, 1, &x); assert(fabs(x - 219.767900) < eps);
    GetMatrix(m3, 1, 0, &x); assert(fabs(x - 322.927000) < eps);
    GetMatrix(m3, 1, 1, &x); assert(fabs(x - 24208.6395) < eps);


    //-----Bad case-----
    Matrix *bad_size;
    bad_size = CreateMatrix(3, OfDouble());
    assert(bad_size != NULL);

    assert(MatrixAdd(m1, m3, bad_size) == 1);
    DestroyMatrix(bad_size);


    Matrix *bad_type;
    bad_type = CreateMatrix(2, OfInt());
    assert(bad_type != NULL);

    assert(MatrixAdd(m1, bad_type, m3) == 1);
    DestroyMatrix(bad_type);
    ////////////////////////////////////

    DestroyMatrix(m1); DestroyMatrix(m2); DestroyMatrix(m3);
}

static void test_multiply_int(void)
{
    //-----Good cases-----
    Matrix *m1, *m2, *m3;
    m1 = CreateMatrix(3, OfInt()); assert(m1);
    m2 = CreateMatrix(3, OfInt()); assert(m2);
    m3 = CreateMatrix(3, OfInt()); assert(m3);
    int value;
    value = 1; assert(SetMatrix(m1, 0, 0, &value) == 0);
    value = 0; assert(SetMatrix(m1, 0, 1, &value) == 0);
    value = 0; assert(SetMatrix(m1, 0, 2, &value) == 0);
    value = 0; assert(SetMatrix(m1, 1, 0, &value) == 0);
    value = 1; assert(SetMatrix(m1, 1, 1, &value) == 0);
    value = 0; assert(SetMatrix(m1, 1, 2, &value) == 0);
    value = 0; assert(SetMatrix(m1, 2, 0, &value) == 0);
    value = 0; assert(SetMatrix(m1, 2, 1, &value) == 0);
    value = 1; assert(SetMatrix(m1, 2, 2, &value) == 0);

    
    value = 312; assert(SetMatrix(m2, 0, 0, &value) == 0); 
    value = 123; assert(SetMatrix(m2, 0, 1, &value) == 0); 
    value = 444; assert(SetMatrix(m2, 0, 2, &value) == 0); 
    value = 512; assert(SetMatrix(m2, 1, 0, &value) == 0); 
    value = 123; assert(SetMatrix(m2, 1, 1, &value) == 0); 
    value = 5; assert(SetMatrix(m2, 1, 2, &value)   == 0); 
    value = 42; assert(SetMatrix(m2, 2, 0, &value)  == 0); 
    value = 52; assert(SetMatrix(m2, 2, 1, &value)  == 0); 
    value = 666; assert(SetMatrix(m2, 2, 2, &value) == 0);

    assert(MatrixMultiply(m1, m2, m3) == 0);

    int x;
    GetMatrix(m3, 0, 0, &x); assert(x == 312);
    GetMatrix(m3, 0, 1, &x); assert(x == 123);
    GetMatrix(m3, 0, 2, &x); assert(x == 444);
    GetMatrix(m3, 1, 0, &x); assert(x == 512);
    GetMatrix(m3, 1, 1, &x); assert(x == 123);
    GetMatrix(m3, 1, 2, &x); assert(x == 5);
    GetMatrix(m3, 2, 0, &x); assert(x == 42);
    GetMatrix(m3, 2, 1, &x); assert(x == 52);
    GetMatrix(m3, 2, 2, &x); assert(x == 666);
    //////////////////////////////////////////

    //-----Bad cases-----
    Matrix *bad_size = CreateMatrix(2, OfInt());
    assert(bad_size);
    assert(MatrixMultiply(m1, bad_size, m3) == 1);
    DestroyMatrix(bad_size);

    Matrix *bad_type = CreateMatrix(3, OfDouble());
    assert(bad_type);
    assert(MatrixMultiply(m1, bad_type, m3) == 1);
    DestroyMatrix(bad_type);


    DestroyMatrix(m1); DestroyMatrix(m2); DestroyMatrix(m3);
}

static void test_multiply_double(void)
{
    //-----Good cases-----
    Matrix *m1, *m2, *m3;
    m1 = CreateMatrix(3, OfDouble()); assert(m1);
    m2 = CreateMatrix(3, OfDouble()); assert(m2);
    m3 = CreateMatrix(3, OfDouble()); assert(m3);
    double value;
    value = 1.0; assert(SetMatrix(m1, 0, 0, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 0, 1, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 0, 2, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 1, 0, &value) == 0);
    value = 1.0; assert(SetMatrix(m1, 1, 1, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 1, 2, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 2, 0, &value) == 0);
    value = 0.0; assert(SetMatrix(m1, 2, 1, &value) == 0);
    value = 1.0; assert(SetMatrix(m1, 2, 2, &value) == 0);

    
    value = 312.0; assert(SetMatrix(m2, 0, 0, &value) == 0); 
    value = 123.0; assert(SetMatrix(m2, 0, 1, &value) == 0); 
    value = 444.0; assert(SetMatrix(m2, 0, 2, &value) == 0); 
    value = 512.0; assert(SetMatrix(m2, 1, 0, &value) == 0); 
    value = 123.0; assert(SetMatrix(m2, 1, 1, &value) == 0); 
    value = 5.0; assert(SetMatrix(m2, 1, 2, &value)   == 0); 
    value = 42.0; assert(SetMatrix(m2, 2, 0, &value)  == 0); 
    value = 52.0; assert(SetMatrix(m2, 2, 1, &value)  == 0); 
    value = 666.0; assert(SetMatrix(m2, 2, 2, &value) == 0);

    assert(MatrixMultiply(m1, m2, m3) == 0);

    double x;
    GetMatrix(m3, 0, 0, &x); assert(fabs(x - 312.0) < eps);
    GetMatrix(m3, 0, 1, &x); assert(fabs(x - 123.0) < eps);
    GetMatrix(m3, 0, 2, &x); assert(fabs(x - 444.0) < eps);
    GetMatrix(m3, 1, 0, &x); assert(fabs(x - 512.0) < eps);
    GetMatrix(m3, 1, 1, &x); assert(fabs(x - 123.0) < eps);
    GetMatrix(m3, 1, 2, &x); assert(fabs(x - 5.0) < eps);
    GetMatrix(m3, 2, 0, &x); assert(fabs(x - 42.0) < eps);
    GetMatrix(m3, 2, 1, &x); assert(fabs(x - 52.0) < eps);
    GetMatrix(m3, 2, 2, &x); assert(fabs(x - 666.0) < eps);
    //////////////////////////////////////////

    //-----Bad cases-----
    Matrix *bad_size = CreateMatrix(2, OfDouble());
    assert(bad_size);
    assert(MatrixMultiply(m1, bad_size, m3) == 1);
    DestroyMatrix(bad_size);

    Matrix *bad_type = CreateMatrix(3, OfInt());
    assert(bad_type);
    assert(MatrixMultiply(m1, bad_type, m3) == 1);
    DestroyMatrix(bad_type);

    DestroyMatrix(m1); DestroyMatrix(m2); DestroyMatrix(m3);
}

static void test_addLinearComb_int(void)
{
    //-----Good cases-----
    Matrix *m;
    m = CreateMatrix(3, OfInt());
    assert(m);

    int value;
    value = 1; assert(SetMatrix(m, 0, 0, &value) == 0);
    value = 2; assert(SetMatrix(m, 0, 1, &value) == 0);
    value = 3; assert(SetMatrix(m, 0, 2, &value) == 0);

    value = 4; assert(SetMatrix(m, 1, 0, &value) == 0);
    value = 5; assert(SetMatrix(m, 1, 1, &value) == 0);
    value = 6; assert(SetMatrix(m, 1, 2, &value) == 0);

    value = 7; assert(SetMatrix(m, 2, 0, &value) == 0);
    value = 8; assert(SetMatrix(m, 2, 1, &value) == 0);
    value = 9; assert(SetMatrix(m, 2, 2, &value) == 0);

    int coeffs[3] = {0, 2, -1};

    assert(AddLinearCombination(m, 1, coeffs) == 0);

    int x;

    GetMatrix(m, 0, 0, &x); assert(x == 1);
    GetMatrix(m, 0, 1, &x); assert(x == 2);
    GetMatrix(m, 0, 2, &x); assert(x == 3);

    // row 1 = row1 + 0*row0 + (-1)*row2 = [4,5,6] + [-7,-8,-9] = [-3,-3,-3]
    // coeff for row1 itself is ignored
    GetMatrix(m, 1, 0, &x); assert(x == -3);
    GetMatrix(m, 1, 1, &x); assert(x == -3);
    GetMatrix(m, 1, 2, &x); assert(x == -3);

   
    GetMatrix(m, 2, 0, &x); assert(x == 7);
    GetMatrix(m, 2, 1, &x); assert(x == 8);
    GetMatrix(m, 2, 2, &x); assert(x == 9);
    //////////////////////////////////////////

    //-----Bad cases-----
    assert(AddLinearCombination(NULL, 1, coeffs) == 1);
    assert(AddLinearCombination(m, 3, coeffs) == 1);
    assert(AddLinearCombination(m, 1, NULL) == 1);

    DestroyMatrix(m);
}

static void test_addLinearComb_double(void)
{
    //-----Good cases-----
    Matrix *m;
    m = CreateMatrix(3, OfDouble());
    assert(m);

    double value;
    value = 1.0; assert(SetMatrix(m, 0, 0, &value) == 0);
    value = 2.0; assert(SetMatrix(m, 0, 1, &value) == 0);
    value = 3.0; assert(SetMatrix(m, 0, 2, &value) == 0);

    value = 4.0; assert(SetMatrix(m, 1, 0, &value) == 0);
    value = 5.0; assert(SetMatrix(m, 1, 1, &value) == 0);
    value = 6.0; assert(SetMatrix(m, 1, 2, &value) == 0);

    value = 7.0; assert(SetMatrix(m, 2, 0, &value) == 0);
    value = 8.0; assert(SetMatrix(m, 2, 1, &value) == 0);
    value = 9.0; assert(SetMatrix(m, 2, 2, &value) == 0);

    double coeffs[3] = {0.5, 0.0, -1.0};

    assert(AddLinearCombination(m, 1, coeffs) == 0);

    double x;

    GetMatrix(m, 0, 0, &x); assert(fabs(x - 1.0) < eps);
    GetMatrix(m, 0, 1, &x); assert(fabs(x - 2.0) < eps);
    GetMatrix(m, 0, 2, &x); assert(fabs(x - 3.0) < eps);

    // row 1 = row1 + 0.5*row0 + (-1.0)*row2
    // [4,5,6] + [0.5,1.0,1.5] + [-7,-8,-9] = [-2.5,-2.0,-1.5]
    GetMatrix(m, 1, 0, &x); assert(fabs(x - (-2.5)) < eps);
    GetMatrix(m, 1, 1, &x); assert(fabs(x - (-2.0)) < eps);
    GetMatrix(m, 1, 2, &x); assert(fabs(x - (-1.5)) < eps);


    GetMatrix(m, 2, 0, &x); assert(fabs(x - 7.0) < eps);
    GetMatrix(m, 2, 1, &x); assert(fabs(x - 8.0) < eps);
    GetMatrix(m, 2, 2, &x); assert(fabs(x - 9.0) < eps);
    //////////////////////////////////////////

    //-----Bad cases-----
    assert(AddLinearCombination(NULL, 1, coeffs) == 1);
    assert(AddLinearCombination(m, 3, coeffs) == 1);
    assert(AddLinearCombination(m, 1, NULL) == 1);

    DestroyMatrix(m);
}

static void test_scalarMultiply_int(void)
{
    //-----Good cases-----
    Matrix *m;
    m = CreateMatrix(3, OfInt());
    assert(m);
    const int scalar = 5;
    int value;
    value = 3; assert(SetMatrix(m, 0, 0, &value) == 0);
    value = 2; assert(SetMatrix(m, 0, 1, &value) == 0);
    value = 1; assert(SetMatrix(m, 0, 2, &value) == 0);
    value = 4; assert(SetMatrix(m, 1, 0, &value) == 0);
    value = 5; assert(SetMatrix(m, 1, 1, &value) == 0);
    value = 6; assert(SetMatrix(m, 1, 2, &value) == 0);
    value = 9; assert(SetMatrix(m, 2, 0, &value) == 0);
    value = 8; assert(SetMatrix(m, 2, 1, &value) == 0);
    value = 7; assert(SetMatrix(m, 2, 2, &value) == 0);

    assert(ScalarMultiply(m, OfInt(), &scalar) == 0);

    int x;
    GetMatrix(m, 0, 0, &x); assert(x == 15);
    GetMatrix(m, 0, 1, &x); assert(x == 10);
    GetMatrix(m, 0, 2, &x); assert(x == 5);
    GetMatrix(m, 1, 0, &x); assert(x == 20);
    GetMatrix(m, 1, 1, &x); assert(x == 25);
    GetMatrix(m, 1, 2, &x); assert(x == 30);
    GetMatrix(m, 2, 0, &x); assert(x == 45);
    GetMatrix(m, 2, 1, &x); assert(x == 40);
    GetMatrix(m, 2, 2, &x); assert(x == 35);
    ///////////////////////////////////////////////////

    //-----Bad cases-----
    assert(ScalarMultiply(NULL, OfInt(), &scalar) == 1);

    double scalar_double = 5.0;
    assert(ScalarMultiply(m, OfDouble(), &scalar_double) == 1);
    assert(ScalarMultiply(m, OfInt(), NULL) == 1);

    DestroyMatrix(m);

}

static void test_scalarMultiply_double(void)
{
    //-----Good cases-----
    Matrix *m;
    m = CreateMatrix(3, OfDouble());
    assert(m);
    const double scalar = 5.0;
    double value;
    value = 3.0; assert(SetMatrix(m, 0, 0, &value) == 0);
    value = 2.0; assert(SetMatrix(m, 0, 1, &value) == 0);
    value = 1.0; assert(SetMatrix(m, 0, 2, &value) == 0);
    value = 4.0; assert(SetMatrix(m, 1, 0, &value) == 0);
    value = 5.0; assert(SetMatrix(m, 1, 1, &value) == 0);
    value = 6.0; assert(SetMatrix(m, 1, 2, &value) == 0);
    value = 9.0; assert(SetMatrix(m, 2, 0, &value) == 0);
    value = 8.0; assert(SetMatrix(m, 2, 1, &value) == 0);
    value = 7.0; assert(SetMatrix(m, 2, 2, &value) == 0);

    assert(ScalarMultiply(m, OfDouble(), &scalar) == 0);

    double x;
    GetMatrix(m, 0, 0, &x); assert(fabs(x - 15.0) < eps);
    GetMatrix(m, 0, 1, &x); assert(fabs(x - 10.0) < eps);
    GetMatrix(m, 0, 2, &x); assert(fabs(x - 5.0) < eps);
    GetMatrix(m, 1, 0, &x); assert(fabs(x - 20.0) < eps);
    GetMatrix(m, 1, 1, &x); assert(fabs(x - 25.0) < eps);
    GetMatrix(m, 1, 2, &x); assert(fabs(x - 30.0) < eps);
    GetMatrix(m, 2, 0, &x); assert(fabs(x - 45.0) < eps);
    GetMatrix(m, 2, 1, &x); assert(fabs(x - 40.0) < eps);
    GetMatrix(m, 2, 2, &x); assert(fabs(x - 35.0) < eps);
    ///////////////////////////////////////////////////

    //-----Bad cases-----
    assert(ScalarMultiply(NULL, OfDouble(), &scalar) == 1);

    int wrong_scalar = 5;
    assert(ScalarMultiply(m, OfInt(), &wrong_scalar) == 1);
    assert(ScalarMultiply(m, OfDouble(), NULL) == 1);

    DestroyMatrix(m);
}

static void test_add_calls_operator(void)
{
    Matrix *a = CreateMatrix(2, FieldSpy(OfDouble()));
    Matrix *b = CreateMatrix(2, FieldSpy(OfDouble()));
    Matrix *out = CreateMatrix(2, FieldSpy(OfDouble()));
    
    spy_reset();

    assert(MatrixAdd(a, b, out) == 0);
    assert(spy_add_calls() == 4);
    
    DestroyMatrix(a);
    DestroyMatrix(b);
    DestroyMatrix(out);
}

static void test_multiply_calls_operator(void)
{
    Matrix *a = CreateMatrix(2, FieldSpy(OfDouble()));
    Matrix *b = CreateMatrix(2, FieldSpy(OfDouble()));
    Matrix *out = CreateMatrix(2, FieldSpy(OfDouble()));

    spy_reset();
    assert(MatrixMultiply(a, b, out) == 0);

    assert(spy_zero_calls() == 4);
    assert(spy_add_calls() == 8);
    assert(spy_multiply_calls() == 8);

    DestroyMatrix(a);
    DestroyMatrix(b);
    DestroyMatrix(out);

}

static void test_create_calls_zero(void)
{
    spy_reset();

    Matrix *m = CreateMatrix(3, FieldSpy(OfDouble()));
    
    assert(spy_zero_calls() == 9);

    DestroyMatrix(m);
}

static void test_print_calls_operator(void)
{
    Matrix *m = CreateMatrix(3, FieldSpy(OfDouble()));
    assert(m);
    spy_reset();

    PrintMatrix(m);
    assert(spy_print_calls() == 9);
    
    DestroyMatrix(m);
}

void run_all_tests(void)
{
    test_create_set_get_int();
    test_create_set_get_double();
    test_sum_int();
    test_sum_double();
    test_multiply_int();
    test_multiply_double();
    test_addLinearComb_int();
    test_addLinearComb_double();
    test_scalarMultiply_int();
    test_scalarMultiply_double();
    test_add_calls_operator();
    test_multiply_calls_operator();
    test_create_calls_zero();
    test_print_calls_operator();

    printf("------------------------\n");
    printf("|   All tests passed.   |\n");
    printf("------------------------\n");
}
