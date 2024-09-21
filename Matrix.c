#include "Matrix.h"

Matrix* InitMatrix(int rows, int cols) {

	Matrix* matrix = malloc(sizeof(Matrix));

	if (matrix == NULL) {
		return NULL;
	}

	// Allocate memory for matrix rows
	matrix->nums = malloc(sizeof(float*) * rows);

	if (matrix->nums == NULL) {
		free(matrix);
		return NULL;
	}

	// Allocate memory for floats in matrix
	for (int i = 0; i < rows; i++) {
		matrix->nums[i] = calloc(cols, sizeof(float));
		if (matrix->nums[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(matrix->nums[j]);
				return NULL;
			}
		}
	}

	matrix->shape[0] = rows;
	matrix->shape[1] = cols;

	return matrix;
}

void FreeMatrix(Matrix* matrix) {
	for (int i = 0; i < matrix->shape[0]; i++) {
		free(matrix->nums[i]);
	}
	free(matrix->nums);
	free(matrix);
}

Matrix* CopyMatrix(Matrix* matrixToCopy) {

	Matrix* matrix = InitMatrix(matrixToCopy->shape[0], matrixToCopy->shape[1]);

	for (int i = 0; i < matrixToCopy->shape[0]; i++) {
		for (int j = 0; j < matrixToCopy->shape[1]; j++) {
			matrix->nums[i][j] = matrixToCopy->nums[i][j];
		}
	}

	return matrix;
}

Matrix* MultiplyMatrix(Matrix* a, Matrix* b, bool inPlace) {

	if (a->shape[1] != b->shape[0]) {
		printf("\nCan't multiply matrix with shape (%d, %d) and matrix with shape (%d, %d)", a->shape[0], a->shape[1], b->shape[0], b->shape[1]);
		return NULL;
	}

	Matrix* c = InitMatrix(a->shape[0], b->shape[1]);
	if (c == NULL) {
		return NULL;
	}

	float total = 0;
	for (int i = 0; i < a->shape[0]; i++) {
		for (int j = 0; j < b->shape[1]; j++) {
			total = 0;
			for (int t = 0; t < b->shape[0]; t++) {
				// i == a row count
				// j == b column count
				// t == b row count

				float x = a->nums[i][t];
				float y = b->nums[t][j];

				total += x * y;
				// printf("\ni: %d, j: %d, t: %d  | %.3f * %.3f | total: %.3f", i, j, t, x, y, total);
			}

			c->nums[i][j] = total;
		}
	}

	if (inPlace) {

		if (a->shape[0] != c->shape[0] || a->shape[1] != c->shape[1]) {
			printf("\nCan't multiply matrix in place with shape (%d, %d) and matrix with shape (%d, %d)", a->shape[0], a->shape[1], c->shape[0], c->shape[1]);
			FreeMatrix(c);
			return NULL;
		}

		for (int i = 0; i < a->shape[0]; i++) {
			for (int j = 0; j < a->shape[1]; j++) {
				a->nums[i][j] = c->nums[i][j];
			}
		}

		FreeMatrix(c);
		c = a;
	}

	return c;
}

Matrix* MultiplyMatrixInPlace(Matrix* a, Matrix* b) {

	if (a->shape[1] != b->shape[0]) {
		printf("\nCan't multiply matrix with shape (%d, %d) and matrix with shape (%d, %d)", a->shape[0], a->shape[1], b->shape[0], b->shape[1]);
		return NULL;
	}

	Matrix* c = InitMatrix(a->shape[0], b->shape[1]);
	if (c == NULL) {
		return NULL;
	}

	float total = 0;
	for (int i = 0; i < a->shape[0]; i++) {
		for (int j = 0; j < b->shape[1]; j++) {
			total = 0;
			for (int t = 0; t < b->shape[0]; t++) {
				// i == a row count
				// j == b column count
				// t == b row count

				float x = a->nums[i][t];
				float y = b->nums[t][j];

				total += x * y;
				// printf("\ni: %d, j: %d, t: %d  | %.3f * %.3f | total: %.3f", i, j, t, x, y, total);
			}

			c->nums[i][j] = total;
		}
	}

	return c;
}

Matrix* SubtractMatrix(Matrix* a, Matrix* b) {

	Matrix* c = InitMatrix(1, 4);

	if (c == NULL) {
		return NULL;
	}

	for (int i = 0; i < c->shape[0]; i++) {
		for (int j = 0; j < c->shape[1]; j++) {
			c->nums[i][j] = a->nums[i][j] - b->nums[i][j];
		}
	}
	
	return c;
}

float DotProduct(Matrix* a, Matrix* b) {

	if (a->shape[0] != b->shape[0] || a->shape[1] != b->shape[1]) {
		printf("\nCan't compute dot product of two matrices with different dimensions: a (%d, %d), b (%d, %d).", a->shape[0], a->shape[1], b->shape[0], b->shape[1]);
		return 500.0f;
	}

	float total = 0;
	for (int i = 0; i < a->shape[0]; i++) {
		for (int j = 0; j < a->shape[1]; j++) {
			total += a->nums[i][j] * b->nums[i][j];
		}
	}

	return total;
}

Matrix* CrossProduct(Matrix* a, Matrix* b, bool normalise) {

	Matrix* c = InitMatrix(1, 4);

	if (c == NULL) {
		return NULL;
	}

	c->nums[0][0] = (a->nums[0][1] * b->nums[0][2]) - (a->nums[0][2] * b->nums[0][1]);
	c->nums[0][1] = (a->nums[0][2] * b->nums[0][0]) - (a->nums[0][0] * b->nums[0][2]);
	c->nums[0][2] = (a->nums[0][0] * b->nums[0][1]) - (a->nums[0][1] * b->nums[0][0]);
	c->nums[0][3] = c->nums[0][2];

	if (normalise) {
		float length = sqrtf(c->nums[0][0] * c->nums[0][0] + c->nums[0][1] * c->nums[0][1] + c->nums[0][2] * c->nums[0][2]);
		c->nums[0][0] /= length;
		c->nums[0][1] /= length;
		c->nums[0][2] /= length;
	}

	return c;
}

void RandomFillMatrix(Matrix* matrix) {
	for (int i = 0; i < matrix->shape[0]; i++) {
		for (int j = 0; j < matrix->shape[1]; j++) {
			matrix->nums[i][j] = rand() % 11;
		}
	}
}

Matrix* ProjectionMatrix(int screenHeight, int screenWidth, float fov, float fNear, float fFar) {

	Matrix* projMatrix = InitMatrix(4, 4);

	if (projMatrix == NULL) {
		return NULL;
	}

	float aspectRatio = (float)screenHeight / screenWidth;
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);

	projMatrix->nums[0][0] = aspectRatio * fovRad;
	projMatrix->nums[1][1] = fovRad;
	projMatrix->nums[2][2] = fFar / (fFar - fNear);
	projMatrix->nums[3][2] = (-fFar * fNear) / (fFar - fNear);
	projMatrix->nums[2][3] = 1.0f;

	return projMatrix;
}

void PrintMatrix(Matrix* matrix) {

	printf("\nMatrix (%d, %d) :\n", matrix->shape[0], matrix->shape[1]);
	for (int i = 0; i < matrix->shape[0]; i++) {
		printf("[ ");
		for (int j = 0; j < matrix->shape[1]; j++) {
			printf("%.3f, ", matrix->nums[i][j]);
		}
		printf("],\n");
	}
}