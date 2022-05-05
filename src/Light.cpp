#include "Light.h"

Light::Light()
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 1.0f;
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat aIntensity)
{
    color = glm::vec3(r, g, b);
    ambient_intensity = aIntensity;
}

void Light::UseLight(GLfloat ambient_intensity_location, GLfloat ambient_color_location)
{
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
}

Light::~Light()
{
}

