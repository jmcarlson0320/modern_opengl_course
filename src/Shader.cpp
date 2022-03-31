#include "Shader.h"
#include "load_shaders.h"

Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader()
{
}

void Shader::fromFile(const char *vertFilename, const char *fragFilename)
{
    shader_info vert_frag_info[] = {
        {GL_VERTEX_SHADER, vertFilename},
        {GL_FRAGMENT_SHADER, fragFilename},
        {GL_NONE, NULL}
    };

    shaderID = load_shaders(vert_frag_info);

    use();
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    clear();
}

GLuint Shader::getProjectionLocation()
{
    return uniformProjection;
}

GLuint Shader::getModelLocation()
{
    return uniformModel;
}

void Shader::use()
{
    glUseProgram(shaderID);
}

void Shader::clear()
{
    glUseProgram(0);
}
