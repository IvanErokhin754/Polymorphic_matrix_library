CC = gcc
all: main

main: main.o FieldOfDouble.o FieldOfInt.o Matrix.o Tests.o FieldSpy.o UI.o
	$(CC) main.o FieldInfo.o FieldOfDouble.o FieldOfInt.o Matrix.o Tests.o FieldSpy.o UI.o -o main

FieldOfDouble.o: FieldOfDouble.c
	$(CC) -c FieldOfDouble.c

FieldOfInt.o: FieldOfInt.c
	$(CC) -c FieldOfInt.c

Matrix.o: Matrix.c
	$(CC) -c Matrix.c

Tests.o: Tests.c
	$(CC) -c Tests.c

FieldSpy.o: FieldSpy.c
	$(CC) -c FieldSpy.c

UI.o: UI.c
	$(CC) -c UI.c
	
clean: 
	rm -f main 

.PHONY: all clean
