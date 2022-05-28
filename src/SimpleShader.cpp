#include "SimpleShader.h"
#include "load_shaders.h"

#include <glm/glm.hpp>

SimpleShader::SimpleShader()
{
    programID = 0;
}

SimpleShader::~SimpleShader()
{
}

void SimpleShader::fromFile(const char *vertFilename, const char *fragFilename)
{
    shader_info info[] = {
        {GL_VERTEX_SHADER, vertFilename},
        {GL_FRAGMENT_SHADER, fragFilename},
        {GL_NONE, NULL}
    };

    programID = load_shaders(info);
}

void SimpleShader::use()
{
    glUseProgram(programID);
}

void SimpleShader::clear()
{
    glUseProgram(0);
}

void SimpleShader::setUniformFloat(const char *name, float value)
{
    GLuint uniformLocation = glGetUniformLocation(programID, name);
    glUniform1f(uniformLocation, value);
}

void SimpleShader::setUniformVec3(const char *name, glm::vec3 value)
{
    GLuint uniformLocation = glGetUniformLocation(programID, name);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void SimpleShader::setUniformMat4(const char *name, glm::mat4 value)
{
    GLuint uniformLocation = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}
