#ifndef SHAPE_H
#define SHAPE_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "Matrix.h"
#include "SDL2/SDL.h"

typedef struct Point3D{
	Matrix* xyz;
} Point3D;

typedef struct Shape {
	Point3D** vertices;
	int numOfVertices;
	bool draw;
} Shape;

typedef struct Mesh {
	Shape** triangles;
	int numOfTriangles;
} Mesh;

extern Matrix* gProjectionMatrix;
extern Matrix* gCamera;
extern int gScreenWidth;
extern int gScreenHeight;

Point3D* InitPoint3D(float x, float y, float z);
void InitPoint3DNoMalloc(Point3D* pointPtr, float x, float y, float z);
Shape* InitShape(Point3D** points, int numOfPoints);
Mesh* InitMesh(Shape** triangles, int numOfTriangles);

Point3D* CopyPoint3D(Point3D* pointToCopy);
Shape* CopyShape(Shape* shapeToCopy);
Mesh* CopyMesh(Mesh* meshToCopy);

Mesh* InitCube();
Mesh* InitTriangle();

void SetScreenWidthHeight(int screenWidth, int screenHeight);
void SetProjectionMatrix(Matrix* projectionMatrix);
void SetCameraPosition(Point3D* xyz);

void ProjectMatrix(Matrix* matrix, Matrix* projMatrix);
void ProjectVertices(Mesh* mesh, Matrix* projMatrix);
void ScaleMatrix(Matrix* matrix);
void ScaleVertices(Mesh* mesh);
void RotateVertices(Mesh* mesh, float theta, double elapsedTime, float speed);
void TranslateVertices(Mesh* mesh, float offset);

int* Interpolate(int x1, int y1, int x2, int y2);

void DrawFilledTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3);
void DrawMesh(Mesh* mesh, SDL_Renderer* renderer, bool rotate, double elapsedTime);

void PrintMesh(Mesh* mesh);

void FreePoint3D(Point3D* point);
void FreeShape(Shape* shape);
void FreeMesh(Mesh* mesh);

#endif