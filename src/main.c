#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengles2.h>
#include "glsl.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		1920, 1080, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
	);
	
	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(0);    // no vsync
	glViewport(0, 0, 1920, 1080); // set view area

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	// Note that a shader can be attached at any point - it does not 
	// necessarily need to be compiled or even have source code before 
	// being attached to a program.

	if (!compile_shader("shader/default_vert.glsl", vshader))
	{
		SDL_Log("Compile Shader Error.\n");
		return 1;
	}

	if (!compile_shader("shader/default_frag.glsl", fshader))
	{
		SDL_Log("Compile Shader Error.\n");
		return 1;
	}

	glLinkProgram(program);
	glUseProgram(program);  // use this shader in the pipeline
	
	GLfloat triangle[] = {
		-0.5f, -0.5f,  // left
		0.0f, 0.5f,    // top
		0.5f, -0.5f    // right
	};

	GLuint vao;
	glGenVertexArraysOES(1, &vao);
	glBindVertexArrayOES(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	// describe the layout of vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	while (!SDL_QuitRequested())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	// free resources
	glDeleteProgram(program);
	glDeleteShader(vshader);
	glDeleteShader(fshader);

	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}
