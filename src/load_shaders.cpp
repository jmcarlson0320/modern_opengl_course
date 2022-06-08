#include "load_shaders.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>

#define MAX_LOG_LENGTH 1024

static char *read_file(const char *filename);

GLuint load_shaders(shader_info *shaders)
{
    if (!shaders) {
        return 0;
    }

    GLuint program = glCreateProgram();

    shader_info *cur = shaders;
    while (cur->type != GL_NONE) {
        // load src from file
        char *src = read_file(cur->filename);

        // compile shader
        cur->shader = glCreateShader(cur->type);
        glShaderSource(cur->shader, 1, &src, NULL);
        free(src);

        glCompileShader(cur->shader);

        // check compilation status
        GLint success;
        glGetShaderiv(cur->shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLuint shader = cur->shader;
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            std::string s(errorLog.begin(), errorLog.end());
            std::cout << s;

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
            return 0;
        }

        // add to program
        glAttachShader(program, cur->shader);

        // get next shader_info struct
        cur++;
    }

    GLint success = 0;
    char err_msg[MAX_LOG_LENGTH] = {'\0'};

    // link program
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, MAX_LOG_LENGTH, NULL, err_msg);
        printf("could not link shaders\n%s", err_msg);
        return 0;
    }

    return program;
}

static char *read_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("could not open file: %s\n", filename);
        return NULL;
    }

    // count the bytes in the file
    fseek(fp, 0, SEEK_END);
    int num_bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer;
    buffer = (char *) malloc(num_bytes + 1);

    // read file into buffer
    int bytes_read = fread(buffer, 1, num_bytes, fp);
    fclose(fp);
    if (bytes_read != num_bytes) {
        printf("could not read from file: %s\n", filename);
        return NULL;
    }
    buffer[num_bytes] = '\0';

    return buffer;
}

