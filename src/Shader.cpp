#include "Shader.h"
#include "load_shaders.h"

Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformView = 0;
    uniformProjection = 0;
    uniformAmbientIntensity = 0;
    uniformAmbientColor = 0;
    uniformDiffuseIntensity = 0;
    uniformDirection = 0;
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
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
    uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
    uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
    uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    clear();
}

GLuint Shader::getProjectionLocation()
{
    return uniformProjection;
}

GLuint Shader::getViewLocation()
{
    return uniformView;
}

GLuint Shader::getModelLocation()
{
    return uniformModel;
}

GLuint Shader::getAmbientIntensityLocation()
{
    return uniformAmbientIntensity;
}

GLuint Shader::getAmbientColorLocation()
{
    return uniformAmbientColor;
}

GLuint Shader::getDiffuseIntensityLocation()
{
    return uniformDiffuseIntensity;
}

GLuint Shader::getDirectionLocation()
{
    return uniformDirection;
}

void Shader::use()
{
    glUseProgram(shaderID);
}

void Shader::clear()
{
    glUseProgram(0);
}
