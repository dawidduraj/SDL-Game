#include <glad/glad.h>
#include <stdio.h>
#include "include/engine.h" 

int engine_init(engine* engine, const char* title, int width, int height){
	printf("Initialising engine...");
	
	// Init SDL2
	if(!SDL_Init()){
		printf("ERROR! SDL_Init: %s\n", SDL_GetError());		   return 0;
	}
	
	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window
	SDL_Window* window = SDL_CreateWindow(engine->title,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, engine->width, engine->height, SDL_WINDOW_OPENGL);

	// Error checking
	if(!window){
		printf("ERROR! SDL_Init: %s\n", SDL_GetError());
		SDL_Quit();
		return 
	}



	return 0;
}

void engine_update(engine* engine){

}

void engine_destroy(engine* engine){

}
