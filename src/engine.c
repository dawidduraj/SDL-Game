#include <glad/glad.h>
#include <SDL.h>
#include <stdio.h>
#include "include/engine.h"

int engine_init(engine *engine, const char *title, int width, int height)
{
	printf("Initialising engine...");
	// Init SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("ERROR! SDL_Init: %s\n", SDL_GetError());
		return 0;
	}

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window
	SDL_Window *window = SDL_CreateWindow(engine->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, engine->width, engine->height, SDL_WINDOW_OPENGL);
	if (!window)
	{
		printf("ERROR! SDL_Window: %s\n", SDL_GetError());
		engine_quit(engine);
		return 0;
	}
	engine->window = window;

	// OpenGL initialisation
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (!glContext)
	{
		printf("ERROR! SDL_GL_CreateContext: %s\n", SDL_GetError());
		engine_quit(engine);
		return 0;
	}
	// Load OpenGL functions using GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("ERROR! Failed to initialize GLAD\n");
		engine_quit(engine);
		return 0;
	}

	glViewport(0, 0, engine->width, engine->height);
	engine->running = 1;
	printf("Engine initialised successfully! OpenGL version: %s\n", glGetString(GL_VERSION));
	return 1;
}

void engine_gameloop(engine *engine)
{
	SDL_Event event;
	while (engine->running)
	{
		// Process events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				engine->running = 0;
			}
		}

		// Clear screen with a color
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers
		SDL_GL_SwapWindow(engine->window);
	}
}

void engine_quit(engine *engine)
{
	printf("Shutting down...");
	SDL_GL_DeleteContext(engine->glContext);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}
