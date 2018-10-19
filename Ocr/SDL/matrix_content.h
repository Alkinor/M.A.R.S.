#ifndef MATRIX_CONTENT_H
#define MATRIX_CONTENT_H
# include <assert.h>
# include <stdio.h>
#include <math.h>

/*Define the Matrix structure :
  - Give access to the dimensions of the matrix
  - Create an array containing the matrix' value*/

typedef struct Matrix
{
	int x;
	int y;
	int* matrix;
}Matrix;

void printMatrix(Matrix mat);
Matrix newMatrix(int x, int y);
void initMatrix(Matrix matrix);
void freeMatrix(Matrix matrix);

#endif
