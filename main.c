#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// #define DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "src/vector.h"

#include "src/Matrix.h"
#include "src/Shape.h"

#define SCREENWIDTH 1080
#define SCREENHEIGHT 640

// Implement culling (not rendering things that are not seen)
// Implement lighting
// Implement clipping fixes
// Implement loading of .obj files

Mesh* MeshFromObjFile(char* pathToObjFile);

int main(int argc, char *argv[]) {

    Mesh* mesh = MeshFromObjFile("./ObjFiles/VideoShip.obj");
    // Mesh* mesh = MeshFromObjFile("./ObjFiles/Cube.obj");

    // Mesh* triangle = InitTriangle();
    // Mesh* mesh = InitCube();

    float aspectRatio = (float) SCREENHEIGHT / SCREENWIDTH;
    printf("\nAspect Ratio: %.5f", aspectRatio);

    SetScreenWidthHeight(SCREENWIDTH, SCREENHEIGHT);
    SetProjectionMatrix(ProjectionMatrix(SCREENHEIGHT, SCREENWIDTH, 90.0f, 0.1f, 1000.0f));
    SetCameraPosition(InitPoint3D(0.0, 0.0, -1.0));

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);
    //Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    //Update the surface
    SDL_UpdateWindowSurface(window);

    //Hack to get window to stay up
    SDL_Event e; 
    bool quit = false;

    clock_t start;
    start = clock();
    double timeElapsed = 0.0f;

    int frameCount = 0;
    int secondCount = 0;
    
    while (quit == false) {

        timeElapsed = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        if (timeElapsed / secondCount > 1.0) {
            printf("\nTime Elapsed: %.2f", timeElapsed);
            printf(" Frames Per Second: %d", frameCount);
            secondCount++;
            frameCount = 0;
        }

        while (SDL_PollEvent(&e)) { 
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        DrawMesh(mesh, renderer, true, timeElapsed);
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

        SDL_RenderPresent(renderer);

        frameCount++;
    }
    
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    FreeMatrix(gProjectionMatrix);
    FreeMatrix(gCamera);
    //FreeMesh(triangle);
    FreeMesh(mesh);

    _CrtDumpMemoryLeaks();

	return 0;
}

Mesh* MeshFromObjFile(char* pathToObjFile) {

    FILE* fptr = fopen(pathToObjFile, "rb");

    char myString[100];

    Vector* pointVector = VectorCreate(sizeof(Point3D), 1000);
    Vector* triangleVector = VectorCreate(sizeof(Shape), 50);
    int idx = 0;

    while (fgets(myString, 100, fptr)) {

        if (myString[0] == 'v' && myString[1] == ' ') {

            float vertex[3] = { 0.0, 1.0, 2.0 };
            int strPtr = 0;
            int vertexPtr = 0;
            char tmpStr[10] = {'\0'};
            for (int i = 2; i < 98; i++) {
                if (myString[i] == '\n') {
                    tmpStr[strPtr] = '\0';
                    strPtr = 0;
                    vertex[vertexPtr] = atof(tmpStr);
                    vertexPtr++;
                    break;
                }

                if (myString[i] == ' ') {
                    tmpStr[strPtr] = '\0';
                    strPtr = 0;
                    vertex[vertexPtr] = atof(tmpStr);
                    vertexPtr++;
                    continue;
                }

                tmpStr[strPtr] = myString[i];

                strPtr++;
            }

            Point3D* tmpPoint = InitPoint3D(vertex[0], vertex[1], vertex[2]);

            VectorAdd(pointVector, tmpPoint);
            idx++;

            free(tmpPoint);
        }
        
        if (myString[0] == 'f' && myString[1] == ' ') {

            int points[3] = { 0 };
            int strPtr = 0;
            int pointPtr = 0;
            char tmpStr[10] = { '\0' };
            for (int i = 2; i < 98; i++) {
                if (myString[i] == '\n') {
                    tmpStr[strPtr] = '\0';
                    strPtr = 0;
                    points[pointPtr] = atoi(tmpStr) - 1;
                    pointPtr++;
                    break;
                }

                if (myString[i] == ' ') {
                    tmpStr[strPtr] = '\0';
                    strPtr = 0;
                    points[pointPtr] = atoi(tmpStr) - 1;
                    pointPtr++;
                    continue;
                }

                tmpStr[strPtr] = myString[i];

                strPtr++;
            }

            Point3D** tmpPoints = malloc(sizeof(Point3D*) * 3);

            tmpPoints[0] = CopyPoint3D(VectorGet(pointVector, points[0]));
            tmpPoints[1] = CopyPoint3D(VectorGet(pointVector, points[1]));
            tmpPoints[2] = CopyPoint3D(VectorGet(pointVector, points[2]));

            Shape* shape = InitShape(tmpPoints, 3);

            VectorAdd(triangleVector, shape);
            // when triangle memcopies to reallocate more memory it messes with the point3d vector as the pointers are shared (theory)

            Shape* s = VectorGet(triangleVector, 0);

            free(shape);
        }
    }

    // Something bad happens when removing and freeing point3d points from vector
    for (int i = 0; i < pointVector->size; i++) {
        Point3D* p = VectorGet(pointVector, i);
        FreeMatrix(p->xyz);
    }
    
    VectorFree(pointVector);

    int numOfTriangles = triangleVector->size;
    Shape** triangles = malloc(sizeof(Shape*) * numOfTriangles);
    
    for (int i = 0; i < triangleVector->size; i++) {
        Shape* shape = VectorGet(triangleVector, i);
        triangles[i] = CopyShape(shape);

        for (int j = 0; j < shape->numOfVertices; j++) {
            FreePoint3D(shape->vertices[j]);
        }

        free(shape->vertices);
    }
    
    VectorFree(triangleVector);

    Mesh* mesh = InitMesh(triangles, numOfTriangles);

    fclose(fptr);

    return mesh;
}