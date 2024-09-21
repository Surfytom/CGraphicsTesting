#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846

typedef struct Matrix {
	float** nums;
	int shape[2];
} Matrix;

Matrix* InitMatrix(int rows, int cols);
void FreeMatrix(Matrix* matrix);
Matrix* CopyMatrix(Matrix* matrixToCopy);

Matrix* MultiplyMatrix(Matrix* a, Matrix* b, bool inPlace);
Matrix* SubtractMatrix(Matrix* a, Matrix* b);
float DotProduct(Matrix* a, Matrix* b);
Matrix* CrossProduct(Matrix* a, Matrix* b, bool normalise);

void RandomFillMatrix(Matrix* matrix);

Matrix* ProjectionMatrix(int screenHeight, int screenWidth, float fov, float fNear, float fFar);

Matrix* CopyMatrix(Matrix* matrix);
void PrintMatrix(Matrix* matrix);