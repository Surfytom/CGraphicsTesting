#include "vector.h"

Vector* VectorCreate(size_t elementSize, size_t initialSize) {
	Vector* vec = malloc(sizeof(Vector));

	if (vec == NULL) { return NULL; }

	vec->elementSize = elementSize;

	vec->elements = malloc(vec->elementSize * initialSize);

	if (vec->elements == NULL) { free(vec); return NULL; }

	vec->size = 0;
	vec->totalSize = initialSize;
}

void VectorFree(Vector* vector) {
	free(vector->elements);
	free(vector);
}

void VectorAdd(Vector* vector, void* element) {
	if (vector->size >= vector->totalSize) {
		// Vector size needs to be increased to accomodate new element

		char* tmpElements = realloc(vector->elements, vector->elementSize * (vector->size + 50));

		if (tmpElements == NULL) {
			printf("\nAttempt to increase vector size with reallocation failed!!!");
		}

		vector->elements = tmpElements;
		vector->totalSize = vector->size + 50;
	}

	memcpy(vector->elements + (vector->elementSize * vector->size), element, vector->elementSize);

	vector->size++;
}

void* VectorRemove(Vector* vector, int index) {
	if (index >= vector->size) {
		printf("\nAttempted to index %d which is out of range of vector with size %d", index, vector->size);
		return NULL;
	}

	void* idx = VectorGet(vector, index);
	printf("Element gotten: %d\n", *(int*)idx);
	for (int i = index; i < vector->size; i++) {
		void* tempIdx = vector->elements + (vector->elementSize * i);
		void* tempIdxplus1 = vector->elements + (vector->elementSize * (i+1));
		memcpy(tempIdx, tempIdxplus1, vector->elementSize);
	}

	vector->size--;
	return idx;
}

void* VectorGet(Vector* vector, int index) {
	if (index >= vector->size) {
		printf("\nAttempted to index %d which is out of range of vector with size %d", index, vector->size);
		return NULL;
	}

	return vector->elements + (vector->elementSize * index);
}