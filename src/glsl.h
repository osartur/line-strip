#ifndef GLSL_UTILS
#define GLSL_UTILS
#include <stdbool.h>
#include <SDL2/SDL_opengles2.h>

bool compile_shader(const char* source_filename, GLuint shader_obj);
char* get_file_content(const char* filename);

#endif
