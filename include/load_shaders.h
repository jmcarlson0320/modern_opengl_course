#ifndef LOAD_SHADERS_H
#define LOAD_SHADERS_H

#include <GL/glew.h>

typedef struct {
    GLenum type;
    const char *filename;
    GLuint shader;
} shader_info;

GLuint load_shaders(shader_info *shaders);

#endif // LOAD_SHADERS_H
