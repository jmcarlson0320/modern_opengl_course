#include "Material.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

Material::Material()
{
    specular_intensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(GLfloat specular_intensity, GLfloat shininess)
{
    this->specular_intensity = specular_intensity;
    this->shininess = shininess;
}

void Material::UseMaterial(GLuint spec_intensity_location, GLuint shininess_location)
{
    glUniform1f(spec_intensity_location, specular_intensity);
    glUniform1f(shininess_location, shininess);
}

Material::~Material()
{
}

