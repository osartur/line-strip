#include "glsl.h"
#include <stdio.h>
#include <stdlib.h>

bool compile_shader(const char* source_filename, GLuint shader_obj)
{
	const char* shader_code = get_file_content(source_filename);
	if (!shader_code)
		return false;

	glShaderSource(shader_obj, 1, &shader_code, NULL);
	glCompileShader(shader_obj);
	free(shader_code);

	GLint status;
	glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status);

	return status;
}

char* get_file_content(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
		return NULL;

	fseek(fp, 0, SEEK_END);
	int size_in_bytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* content = (char*) malloc(size_in_bytes + 1 * sizeof(char));
	int i = 0;
	int ch;
	while ((ch = fgetc(fp)) != EOF)
		content[i++] = ch;
	content[i] = '\0';

	fclose(fp);

	return content;
}

