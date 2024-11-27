#include <glad/glad.h>
#include <SDL.h>
#include <stdio.h>
#include "include/engine.h"

int SDL_main(int argc, char *argv[])
{
    // init engine
    engine gameengine = {0};
    if (!engine_init(&gameengine, ENGINE_DEFAULT_TITLE, ENGINE_DEFAULT_WIDTH, ENGINE_DEFAULT_HEIGHT))
    {
        return 1;
    }

    // Main loop
    engine_gameloop(&gameengine);

    engine_quit(&gameengine);
    return 0;
}
