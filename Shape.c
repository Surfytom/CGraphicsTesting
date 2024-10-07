#include "Shape.h"

Matrix* gProjectionMatrix = NULL;
int gScreenWidth = 0;
int gScreenHeight = 0;

Point3D* InitPoint3D(float x, float y, float z) {
	Matrix* pointMatrix = InitMatrix(1, 4);

	if (pointMatrix == NULL) {
		return NULL;
	}

	Point3D* point3D = malloc(sizeof(Point3D));

	if (point3D == NULL) {
		FreeMatrix(pointMatrix);
		return NULL;
	}

	pointMatrix->nums[0][0] = x;
	pointMatrix->nums[0][1] = y;
	pointMatrix->nums[0][2] = z;
	pointMatrix->nums[0][3] = z;

	point3D->xyz = pointMatrix;

	return point3D;
}

Point3D* CopyPoint3D(Point3D* pointToCopy) {
	Point3D* point = malloc(sizeof(Point3D));

	if (point == NULL) {
		return NULL;
	}
	
	point->xyz = CopyMatrix(pointToCopy->xyz);

	return point;
}

void InitPoint3DNoMalloc(Point3D* pointPtr, float x, float y, float z) {
	Matrix* pointMatrix = InitMatrix(1, 4);

	if (pointMatrix == NULL) {
		return NULL;
	}

	pointMatrix->nums[0][0] = x;
	pointMatrix->nums[0][1] = y;
	pointMatrix->nums[0][2] = z;
	pointMatrix->nums[0][3] = z;

	pointPtr->xyz = pointMatrix;
}


/*
Shape* InitShape(Matrix* vertices) {

	if (vertices->shape[1] > 4 || vertices->shape[1] < 4) {
		printf("Vertices need to be length of 4. Has length %d", vertices->shape[1]);
		return NULL;
	}

	Shape* shape = malloc(sizeof(Shape));

	if (shape == NULL) {
		return NULL;
	}

	shape->vertices = vertices;

	return shape;
}
*/

Shape* InitShape(Point3D** points, int numOfPoints) {

	Shape* shape = malloc(sizeof(Shape));

	if (shape == NULL) {
		return NULL;
	}

	shape->vertices = points;
	shape->numOfVertices = numOfPoints;

	return shape;
}

Shape* CopyShape(Shape* shapeToCopy) {
	Shape* shape = malloc(sizeof(Shape));

	if (shape == NULL) {
		return NULL;
	}

	shape->vertices = malloc(sizeof(Point3D*) * shapeToCopy->numOfVertices);

	if (shape->vertices == NULL) {
		free(shape);
		return NULL;
	}

	for (int i = 0; i < shapeToCopy->numOfVertices; i++) {
		shape->vertices[i] = CopyPoint3D(shapeToCopy->vertices[i]);
	}
	shape->numOfVertices = shapeToCopy->numOfVertices;

	return shape;
}

/*
Shape* InitTriangle(float x, float y, float z) {
	Matrix* triVertices = InitMatrix(1, 4);

	if (triVertices == NULL) {
		return NULL;
	}

	triVertices->nums[0][0] = x;
	triVertices->nums[0][1] = y;
	triVertices->nums[0][2] = z;
	triVertices->nums[0][3] = z;

	Shape* triShape = InitShape(triVertices);

	if (triShape == NULL) {
		FreeMatrix(triVertices);
		return NULL;
	}

	return triShape;
}
*/

Mesh* InitMesh(Shape** triangles, int numOfTriangles) {
	Mesh* mesh = malloc(sizeof(Mesh));

	if (mesh == NULL) {
		return NULL;
	}

	mesh->triangles = triangles;
	mesh->numOfTriangles = numOfTriangles;

	return mesh;
}

Mesh* CopyMesh(Mesh* meshToCopy) {
	Mesh* mesh = malloc(sizeof(Mesh));

	if (mesh == NULL) {
		return NULL;
	}

	mesh->triangles = malloc(sizeof(Shape*) * meshToCopy->numOfTriangles);

	if (mesh->triangles == NULL) {
		FreeMesh(mesh);
		return NULL;
	}
	
	for (int i = 0; i < meshToCopy->numOfTriangles; i++) {
		mesh->triangles[i] = CopyShape(meshToCopy->triangles[i]);
	}
	mesh->numOfTriangles = meshToCopy->numOfTriangles;

	return mesh;
}

Mesh* InitTriangle() {
	Shape** tri = malloc(sizeof(Shape*) * 1);

	if (tri == NULL) {
		return NULL;
	}

	Point3D** points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tri);
		return NULL;
	}
	
	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(-0.2, -0.25, 0);
	points[2] = InitPoint3D(-0.25, -0.5, 0);

	tri[0] = InitShape(points, 3);

	Mesh* triangle = InitMesh(tri, 1);

	return triangle;
}

Mesh* InitCube() {

	Shape** tris = malloc(sizeof(Shape*) * 12);

	if (tris == NULL) {
		return NULL;
	}

	Point3D** points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	// South Face
	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(0, 1, 0);
	points[2] = InitPoint3D(1, 1, 0);

	tris[0] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(1, 1, 0);
	points[2] = InitPoint3D(1, 0, 0);

	tris[1] = InitShape(points, 3);

	// North Face
	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 0, 1);
	points[1] = InitPoint3D(1, 1, 1);
	points[2] = InitPoint3D(0, 1, 1);

	tris[2] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 0, 1);
	points[1] = InitPoint3D(0, 1, 1);
	points[2] = InitPoint3D(0, 0, 1);

	tris[3] = InitShape(points, 3);

	// West Face
	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(0, 1, 1);
	points[2] = InitPoint3D(0, 1, 0);

	tris[4] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(0, 0, 1);
	points[2] = InitPoint3D(0, 1, 1);

	tris[5] = InitShape(points, 3);

	// East Face
	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 0, 0);
	points[1] = InitPoint3D(1, 1, 0);
	points[2] = InitPoint3D(1, 1, 1);

	tris[6] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 0, 0);
	points[1] = InitPoint3D(1, 1, 1);
	points[2] = InitPoint3D(1, 0, 1);

	tris[7] = InitShape(points, 3);

	// Top Face
	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(0, 1, 0);
	points[1] = InitPoint3D(0, 1, 1);
	points[2] = InitPoint3D(1, 1, 0);

	tris[8] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 1, 0);
	points[1] = InitPoint3D(0, 1, 1);
	points[2] = InitPoint3D(1, 1, 1);

	tris[9] = InitShape(points, 3);

	// Bottom Face
	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(0, 0, 0);
	points[1] = InitPoint3D(1, 0, 0);
	points[2] = InitPoint3D(0, 0, 1);

	tris[10] = InitShape(points, 3);

	points = malloc(sizeof(Point3D*) * 3);

	if (points == NULL) {
		free(tris);
		return NULL;
	}

	points[0] = InitPoint3D(1, 0, 0);
	points[1] = InitPoint3D(1, 0, 1);
	points[2] = InitPoint3D(0, 0, 1);

	tris[11] = InitShape(points, 3);

	Mesh* cube = InitMesh(tris, 12);

	return cube;
}

void SetProjectionMatrix(Matrix* projectionMatrix) {
	gProjectionMatrix = projectionMatrix;
}

void SetCameraPosition(Point3D* xyz) {
	gCamera = xyz->xyz;
	free(xyz);
}

void SetScreenWidthHeight(int screenWidth, int screenHeight) {
	gScreenWidth = screenWidth;
	gScreenHeight = screenHeight;
}

void ProjectVertices(Mesh* mesh, Matrix* projMatrix) {
	for (int i = 0; i < mesh->numOfTriangles; i++) {
		for (int j = 0; j < mesh->triangles[0]->numOfVertices; j++) {

			MultiplyMatrix(mesh->triangles[i]->vertices[j]->xyz, projMatrix, true);

			if (mesh->triangles[i]->vertices[j]->xyz->nums[0][3] != 0.0f) {
				mesh->triangles[i]->vertices[j]->xyz->nums[0][0] /= mesh->triangles[i]->vertices[j]->xyz->nums[0][3];
				mesh->triangles[i]->vertices[j]->xyz->nums[0][1] /= mesh->triangles[i]->vertices[j]->xyz->nums[0][3];
				mesh->triangles[i]->vertices[j]->xyz->nums[0][2] /= mesh->triangles[i]->vertices[j]->xyz->nums[0][3];
			}
		}
	}
}

void TranslateVertices(Mesh* mesh, float offset) {
	for (int i = 0; i < mesh->numOfTriangles; i++) {
		for (int j = 0; j < mesh->triangles[0]->numOfVertices; j++) {
			mesh->triangles[i]->vertices[j]->xyz->nums[0][2] += offset;
		}
	}
}

void ScaleVertices(Mesh* mesh) {
	for (int i = 0; i < mesh->numOfTriangles; i++) {
		for (int j = 0; j < mesh->triangles[0]->numOfVertices; j++) {
			mesh->triangles[i]->vertices[j]->xyz->nums[0][0] += 1.0f;
			mesh->triangles[i]->vertices[j]->xyz->nums[0][1] += 1.0f;

			mesh->triangles[i]->vertices[j]->xyz->nums[0][0] *= 0.5f * (float)gScreenWidth;
			mesh->triangles[i]->vertices[j]->xyz->nums[0][1] *= 0.5f * (float)gScreenHeight;
		}
	}
}

void RotateVertices(Mesh* mesh, float theta, double elapsedTime, float speed) {

	Matrix* rotateX = InitMatrix(4, 4);

	if (rotateX == NULL) {
		return NULL;
	}

	Matrix* rotateZ = InitMatrix(4, 4);

	if (rotateZ == NULL) {
		FreeMatrix(rotateX);
		return NULL;
	}

	Matrix* rotateY = InitMatrix(4, 4);

	if (rotateY == NULL) {
		FreeMatrix(rotateX);
		FreeMatrix(rotateZ);
		return NULL;
	}

	theta += (float) 1.0f * (elapsedTime * speed);

	rotateX->nums[0][0] = 1.0f;
	rotateX->nums[1][1] = cosf(theta * 0.5f);
	rotateX->nums[1][2] = -sinf(theta * 0.5f);
	rotateX->nums[2][1] = sinf(theta * 0.5f);
	rotateX->nums[2][2] = cosf(theta * 0.5f);
	rotateX->nums[3][3] = 1.0f;
	
	rotateY->nums[0][0] = cosf(theta);
	rotateY->nums[0][2] = sinf(theta);
	rotateY->nums[1][1] = 1.0f;
	rotateY->nums[2][0] = -sinf(theta);
	rotateY->nums[2][2] = cosf(theta);
	rotateY->nums[3][3] = 1.0f;

	rotateZ->nums[0][0] = cosf(theta);
	rotateZ->nums[0][1] = -sinf(theta);
	rotateZ->nums[1][0] = sinf(theta);
	rotateZ->nums[1][1] = cosf(theta);
	rotateZ->nums[2][2] = 1.0f;
	rotateZ->nums[3][3] = 1.0f;

	for (int i = 0; i < mesh->numOfTriangles; i++) {
		for (int j = 0; j < mesh->triangles[0]->numOfVertices; j++) {
			MultiplyMatrix(mesh->triangles[i]->vertices[j]->xyz, rotateX, true);
			MultiplyMatrix(mesh->triangles[i]->vertices[j]->xyz, rotateY, true);
			MultiplyMatrix(mesh->triangles[i]->vertices[j]->xyz, rotateZ, true);
		}
	}

	FreeMatrix(rotateX);
	FreeMatrix(rotateY);
	FreeMatrix(rotateZ);
}

Matrix* Normal(Shape* triangle) {

	Matrix* line1 = SubtractMatrix(triangle->vertices[1]->xyz, triangle->vertices[0]->xyz);

	if (line1 == NULL) {
		return NULL;
	}

	Matrix* line2 = SubtractMatrix(triangle->vertices[2]->xyz, triangle->vertices[0]->xyz);

	if (line2 == NULL) {
		FreeMatrix(line1);
		return NULL;
	}
	
	Matrix* normal = CrossProduct(line1, line2, true);

	if (normal == NULL) {
		FreeMatrix(line1);
		FreeMatrix(line2);
		return NULL;
	}

	FreeMatrix(line1);
	FreeMatrix(line2);

	return normal;
}

int* Interpolate(int x1, int y1, int x2, int y2) {
	// (x) = x1 + [(y-y1) × (x2-x1)] / (y2-y1)

	int* xValues = malloc(sizeof(int) * (y2 - y1));

	if (xValues == NULL) {
		return NULL;
	}

#ifdef DEBUG
	printf("\nInterpolate between x1 %d, y1 %d and x2 %d, y2 %d", x1, y1, x2, y2);
#endif // DEBUG

	int interpPoint = 0;
	for (int i = y1; i < y2; i++) {
		interpPoint = x1 + ((i - y1) * (x2 - x1)) / (y2 - y1);
#ifdef DEBUG
		printf("\nInterp Point for y %d: %d, index: %d", i, interpPoint, i - y1);
#endif // DEBUG
		xValues[i - y1] = interpPoint;
	}

	return xValues;
}

void DrawFilledTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3) {

	int sortedYPoints[] = { y1, y2, y3 };
	int sortedXPoints[] = { x1, x2, x3 };

#ifdef DEBUG
	printf("\nTriangle points before sort: ");
	for (int i = 0; i < 3; i++) {
		printf("\nPoint %d: x %d, y %d", i, sortedXPoints[i], sortedYPoints[i]);
	}
#endif // DEBUG

	int tempXPoint = 0;
	int tempYPoint = 0;
	if (sortedYPoints[1] < sortedYPoints[0]) {
		tempYPoint = sortedYPoints[0];
		tempXPoint = sortedXPoints[0];

		sortedYPoints[0] = sortedYPoints[1];
		sortedYPoints[1] = tempYPoint;

		sortedXPoints[0] = sortedXPoints[1];
		sortedXPoints[1] = tempXPoint;

	}
	if (sortedYPoints[2] < sortedYPoints[0]) {
		tempYPoint = sortedYPoints[0];
		tempXPoint = sortedXPoints[0];

		sortedYPoints[0] = sortedYPoints[2];
		sortedYPoints[2] = tempYPoint;

		sortedXPoints[0] = sortedXPoints[2];
		sortedXPoints[2] = tempXPoint;
	}
	if (sortedYPoints[2] < sortedYPoints[1]) {
		tempYPoint = sortedYPoints[1];
		tempXPoint = sortedXPoints[1];

		sortedYPoints[1] = sortedYPoints[2];
		sortedYPoints[2] = tempYPoint;

		sortedXPoints[1] = sortedXPoints[2];
		sortedXPoints[2] = tempXPoint;
	}

#ifdef DEBUG
	printf("\nTriangle points after sort: ");
	for (int i = 0; i < 3; i++) {
		printf("\nPoint %d: x %d, y %d", i, sortedXPoints[i], sortedYPoints[i]);
	}
#endif // DEBUG

	int* interp0to2 = Interpolate(sortedXPoints[0], sortedYPoints[0], sortedXPoints[2], sortedYPoints[2]);
	int* interp0to1 = Interpolate(sortedXPoints[0], sortedYPoints[0], sortedXPoints[1], sortedYPoints[1]);
	int* interp1to2 = Interpolate(sortedXPoints[1], sortedYPoints[1], sortedXPoints[2], sortedYPoints[2]);

#ifdef DEBUG
	printf("\nlength of both 0 to 1: %d", sortedYPoints[1] - sortedYPoints[0]);
	printf("\nlength of both 1 to 2: %d", sortedYPoints[2] - sortedYPoints[1]);
	printf("\nlength of both arrays combined: %d", (sortedYPoints[1] - sortedYPoints[0]) + (sortedYPoints[2] - sortedYPoints[1]));
#endif // DEBUG

	int* interp0to1to2 = malloc(sizeof(int) * ((sortedYPoints[1] - sortedYPoints[0]) + (sortedYPoints[2] - sortedYPoints[1])));

	if (interp0to1to2 == NULL) {
		free(interp0to2);
		free(interp0to1);
		free(interp1to2);
		return NULL;
	}

	for (int i = 0; i < (sortedYPoints[1] - sortedYPoints[0]); i++) {
		interp0to1to2[i] = interp0to1[i];
	}

	for (int i = 0; i < (sortedYPoints[2] - sortedYPoints[1]); i++) {
		interp0to1to2[(sortedYPoints[1] - sortedYPoints[0])+i] = interp1to2[i];
	}

	int len = sortedYPoints[2] - sortedYPoints[0];

	int m = (int)floor(len / 2);

	int* xLeft;
	int* xRight;

	if (interp0to2[m] < interp0to1to2[m]) {
		xLeft = interp0to2;
		xRight = interp0to1to2;
	} else {
		xLeft = interp0to1to2;
		xRight = interp0to2;
	}

	for (int i = sortedYPoints[0]; i < sortedYPoints[2]; i++) {
		for (int j = xLeft[i - sortedYPoints[0]]; j < xRight[i - sortedYPoints[0]]; j++) {
			SDL_RenderDrawPoint(renderer, j, i);
		}
	}

	free(interp0to2);
	free(interp0to1);
	free(interp1to2);
	free(interp0to1to2);
}

void DrawMesh(Mesh* mesh, SDL_Renderer* renderer, bool rotate, double elapsedTime) {

	// printf("\n\nOriginal Mesh:");
	// PrintMesh(mesh);

	Mesh* copyOfMesh = CopyMesh(mesh);

	if (copyOfMesh == NULL) {
		return NULL;
	}

	// printf("\n\nCopy Of Mesh:");
	// PrintMesh(copyOfMesh);

	if (gProjectionMatrix == NULL) {
		printf("\nProjection Matrix not set.");
		return;
	}

	int speed = 1;
	if (!rotate) {
		speed = 0;
	}
	
	RotateVertices(copyOfMesh, 0.0f, elapsedTime, speed);
	TranslateVertices(copyOfMesh, 10.0f);

	// Check if normal is in view
	for (int i = 0; i < copyOfMesh->numOfTriangles; i++) {
		Matrix* normal = Normal(copyOfMesh->triangles[i]);

		if (normal == NULL) {
			continue;
		}

		Matrix* line = SubtractMatrix(copyOfMesh->triangles[i]->vertices[0]->xyz, gCamera);

		if (normal == NULL) {
			FreeMatrix(normal);
			break;
		}

		float dotProduct = DotProduct(line, normal);

		if (dotProduct < 0.0f) {
			copyOfMesh->triangles[i]->draw = true;
		}
		else {
			copyOfMesh->triangles[i]->draw = false;
		}

		FreeMatrix(normal);
		FreeMatrix(line);
	}

	// Project Shapes Points
	ProjectVertices(copyOfMesh, gProjectionMatrix);

	// Scale Shapes Points
	ScaleVertices(copyOfMesh);

	for (int i = 0; i < copyOfMesh->numOfTriangles; i++) {
		if (copyOfMesh->triangles[i]->draw) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderDrawLine(renderer, (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][1], (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][1]);
			SDL_RenderDrawLine(renderer, (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][1], (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][1]);
			SDL_RenderDrawLine(renderer, (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][1], (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][1]);
			
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			DrawFilledTriangle(renderer, (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[0]->xyz->nums[0][1], (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[1]->xyz->nums[0][1], (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][0], (int)copyOfMesh->triangles[i]->vertices[2]->xyz->nums[0][1]);
		}
	}

	FreeMesh(copyOfMesh);
}

void PrintMesh(Mesh* mesh) {
	for (int i = 0; i < mesh->numOfTriangles; i++) {
		printf("\nTriangle %d", i);
		for (int j = 0; j < mesh->triangles[0]->numOfVertices; j++) {
			printf("\nVertex %d", j);
			PrintMatrix(mesh->triangles[i]->vertices[j]->xyz);
		}
	}
}

void FreePoint3D(Point3D* point) {
	FreeMatrix(point->xyz);
	free(point);
}

void FreeShape(Shape* shape) {
	for (int i = 0; i < shape->numOfVertices; i++) {
		FreePoint3D(shape->vertices[i]);
	}

	free(shape->vertices);
	free(shape);
}

void FreeMesh(Mesh* mesh) {
	for (int i = 0; i < mesh->numOfTriangles; i++) {
		FreeShape(mesh->triangles[i]);
	}

	free(mesh->triangles);
	free(mesh);
}