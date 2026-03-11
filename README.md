# Lab 1 - Polymorphic Matrix Library

Implementation of a polymorphic square matrix library in C.

## Supported fields

- int
- double

## Matrix operations

- Create / destroy matrix
- Set element
- Print matrix
- Matrix addition
- Matrix multiplication
- Scalar multiplication
- Add linear combination of rows

## Architecture

Polymorphism is implemented using the `FieldInfo` structure with function pointers:

- zero
- add
- multiply
- print
- read

Each field (`int`, `double`) provides its own implementation.

## Testing

Unit tests are implemented in `Tests.c`.

`FieldSpy` is used to verify correct usage of field operations.
