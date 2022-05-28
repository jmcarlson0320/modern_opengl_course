#include "Shader.h"
#include "load_shaders.h"

Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformView = 0;
    uniformProjection = 0;
    uniformEyePosition = 0;
    uniformAmbientIntensity = 0;
    uniformLightColor = 0;
    uniformLightIntensity = 0;
    uniformLightDirection = 0;
    uniformSpecularIntensity = 0;
    uniformShininess = 0;
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
    uniformEyePosition = glGetUniformLocation(shaderID, "eye");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "ambientIntensity");
    uniformLightColor = glGetUniformLocation(shaderID, "lightColor");
    uniformLightIntensity = glGetUniformLocation(shaderID, "lightIntensity");
    uniformLightDirection = glGetUniformLocation(shaderID, "lightDirection");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specular_intensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
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

GLuint Shader::getEyePositionLocation()
{
    return uniformEyePosition;
}

GLuint Shader::getAmbientIntensityLocation()
{
    return uniformAmbientIntensity;
}

GLuint Shader::getLightColorLocation()
{
    return uniformLightColor;
}

GLuint Shader::getLightIntensityLocation()
{
    return uniformLightIntensity;
}

GLuint Shader::getLightDirectionLocation()
{
    return uniformLightDirection;
}

GLuint Shader::getSpecularIntensityLocation()
{
    return uniformSpecularIntensity;
}

GLuint Shader::getShininessLocation()
{
    return uniformShininess;
}

void Shader::use()
{
    glUseProgram(shaderID);
}

void Shader::clear()
{
    glUseProgram(0);
}
