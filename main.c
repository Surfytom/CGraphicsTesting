#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// #define DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Matrix.h"
#include "Shape.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

// Implement culling (not rendering things that are not seen)
// Implement lighting
// Implement clipping fixes
// Implement loading of .obj files

int main() {

    // Mesh* triangle = InitTriangle();
    Mesh* triangle = InitCube();

    float aspectRatio = (float) SCREENHEIGHT / SCREENWIDTH;
    printf("Aspect Ratio: %.5f", aspectRatio);

    SetScreenWidthHeight(SCREENWIDTH, SCREENHEIGHT);

    Matrix* projMatrix = ProjectionMatrix(SCREENHEIGHT, SCREENWIDTH, 90.0f, 0.1f, 1000.0f);
    PrintMatrix(projMatrix);

    SetProjectionMatrix(projMatrix);

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
    
    while (quit == false) {
        timeElapsed = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        printf("\nTime Elapsed: %f", timeElapsed);
        while (SDL_PollEvent(&e)) { 
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        DrawMesh(triangle, renderer, true, timeElapsed);
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

        SDL_RenderPresent(renderer);
    }
    
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    FreeMatrix(gProjectionMatrix);
    FreeMesh(triangle);

    _CrtDumpMemoryLeaks();

	return 0;
}