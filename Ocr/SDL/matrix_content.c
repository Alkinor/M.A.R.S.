#include "matrix_content.h"
#include <stdio.h>
#include <stdlib.h>

/*The matrix structure is defined
in the header file*/

//Print the content of the matrix

void printMatrix(Matrix matrix) 
{
	for (int i = 0; i < matrix.x; i++)
	{
		for (int j = 0; j < matrix.y; j++)
		{
			printf("%d ", matrix.matrix[j+i*matrix.y]); 
		}
		printf("\n");
	}
}

//Build a new matrix

Matrix newMatrix(int x, int y) 
{
	Matrix matrix;
	matrix.x = x;
	matrix.y = y;
	//Allocate some space for the matrix to store values
	matrix.matrix = malloc(x * y * sizeof(int));
	return(matrix);
}

//Fill the matrix with 0

void initMatrix(Matrix matrix)
{
  for (int i = 0; i < matrix.x; i++)
    {
      for (int j = 0; j < matrix.y; j++)
	{
	  matrix.matrix[j + i * matrix.y] = 0;
	  //This works like matrix.matrix[i,j]
	}
    }
}

//Free the allocated space to store values in the matrix

void freeMatrix(Matrix matrix)
{
  free(matrix.matrix);
}

