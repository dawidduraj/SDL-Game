#include <glad/glad.h>
#include <SDL.h>
#include <stdio.h>
#include "include/engine.h"

// TODO: Create Data Structures (gfx.h)
GLuint g_VAO = 0;
GLuint g_VBO = 0;
GLuint g_ShaderProgram;
const char *g_vertexShaderSource =
	"#version 410 core\n"
	"in vec4 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
	"}\n";
const char *g_fragmentShaderSource =
	"#version 410 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	color = vec4(1.f, 0.5f, 0.0f, 1.0f);\n"
	"}\n";
// TODO: Overload with given title, height, wight
int engine_init(engine *engine)
{
	printf("Initialising engine...\n");
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
	// TODO: Allow for changing attributes
	SDL_Window *window = SDL_CreateWindow(ENGINE_DEFAULT_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ENGINE_DEFAULT_WIDTH, ENGINE_DEFAULT_HEIGHT, SDL_WINDOW_OPENGL);
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
	engine->glContext = glContext;
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

	// setup graphics
	engine_vertexspecification();
	creategraphicspipeline();
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

		// predraw
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		// TODO: Change to var
		glViewport(0, 0, ENGINE_DEFAULT_WIDTH, ENGINE_DEFAULT_HEIGHT);
		// Clear screen with a color
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(g_ShaderProgram);
		// draw
		glBindVertexArray(g_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, g_VBO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
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

void engine_vertexspecification()
{
	// draw basic triangle
	const GLfloat vertecies[] = {
		// x     y     z
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f};

	glGenVertexArrays(1, &g_VAO);
	glBindVertexArray(g_VAO);

	glGenBuffers(1, &g_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
	// may be wrong
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies) * sizeof(GLfloat), vertecies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Cleanup
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}
GLuint CompileShader(const GLuint type, const char *source)
{
	GLuint shaderObject = 0;
	if (type == GL_VERTEX_SHADER)
	{
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == GL_FRAGMENT_SHADER)
	{
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(shaderObject, 1, &source, NULL);
	glCompileShader(shaderObject);
	// TODO: Log compile error
	int success;
	char infoLog[512];
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
	if (!success)
	{
		// TODO: Format
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
	}
	return shaderObject;
}
GLuint createshaderprogram(const char *vertexShader, const char *fragmentShader)
{
	GLuint shaderprogram = glCreateProgram();
	GLuint compiledVertexShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint compiledFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(shaderprogram, compiledVertexShader);
	glAttachShader(shaderprogram, compiledFragmentShader);
	glLinkProgram(shaderprogram);
	// Error checking
	glValidateProgram(shaderprogram);
	// glDetachShader, glDeleteShader
	return shaderprogram;
}
void creategraphicspipeline()
{
	g_ShaderProgram = createshaderprogram(g_vertexShaderSource, g_fragmentShaderSource);
}