#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

// Constants
#define ENGINE_DEFAULT_WIDTH 800
#define ENGINE_DEFAULT_HEIGHT 600
#define ENGINE_DEFAULT_TITLE "SDL Game v0.1"

// Structs
typedef struct
{
    SDL_Window *window;
    SDL_GLContext glContext;
    int width;
    int height;
    int running;
    char *title;
} engine;

// Functions
int engine_init(engine *engine, const char *title, int width, int height);
void engine_gameloop(engine *engine);
void engine_quit(engine *engine);
#endif
