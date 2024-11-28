#define SDL_MAIN_HANDLED
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "include/engine.h"

int main(int argc, char *argv[])
{
    // init engine
    engine gameengine = {0};
    if (!engine_init(&gameengine))
    {
        return 1;
    }

    // Main loop
    engine_gameloop(&gameengine);

    engine_quit(&gameengine);
    return 0;
}
