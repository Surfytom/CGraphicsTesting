#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

#include "Shape.h"

typedef struct Vector {
	char* elements;
	size_t elementSize;
	size_t size;
	size_t totalSize;
} Vector;

Vector* VectorCreate(size_t elementSize, size_t initialSize);
void VectorFree(Vector* vector);

void VectorAdd(Vector* vector, void* element);
void* VectorRemove(Vector* vector, int index);
void* VectorGet(Vector* vector, int index);

#endif