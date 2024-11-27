#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

// Constants
#define WINDOW_DEFAULT_WIDTH 800
#define WINDOW_DEFAULT_HEIGHT 600
#define WINDOW_DEFAULT_TITLE "SDL Game v0.1"

// Structs
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext glContext;
    int width;
    int height;
    int running;
    char* title;
} engine;

// Functions
int engine_init(engine* engine, const char* title, int width, int height);
void engine_update(engine* engine);
void engine_destroy(engine* engine);
#endif

