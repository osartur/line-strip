#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengles2.h>
#include <stdlib.h>
#include "glsl.h"

int main(int argc, char *argv[])
{
	int total_vertexes = 10;
	if (argc == 2)
		total_vertexes = atoi(argv[1]);
	
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

	SDL_GL_SetSwapInterval(0);
	glViewport(0, 0, 1920, 1080);

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);

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
	glUseProgram(program);
	
	GLuint vao;
	glGenVertexArraysOES(1, &vao);
	glBindVertexArrayOES(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, total_vertexes * 2 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	GLfloat v[2];
	int i = 0;
	int size = 0;

	while (!SDL_QuitRequested())
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_FINGERDOWN)
			{
				v[0] = (ev.tfinger.x - 0.5f) / 0.5f;
				v[1] = (0.5f - ev.tfinger.y) / 0.5f;
				glBufferSubData(GL_ARRAY_BUFFER, i * 2 * sizeof(GLfloat), 2 * sizeof(GLfloat), v);

				i = (i + 1) % total_vertexes;
				if (size < total_vertexes)
					size++;
			}
		}

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_LINE_STRIP, 0, size);

		SDL_GL_SwapWindow(window);
	}

	glDeleteProgram(program);
	glDeleteShader(vshader);
	glDeleteShader(fshader);

	glDeleteVertexArraysOES(1, &vao);
	glDeleteBuffers(1, &vbo);

	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}
