#include "Light.h"

Light::Light()
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 1.0f;
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambient_intensity,
        GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuse_intensity)
{
    color = glm::vec3(r, g, b);
    this->ambient_intensity = ambient_intensity;
    direction = glm::vec3(xDir, yDir, zDir);
    this->diffuse_intensity = diffuse_intensity;
}

void Light::UseLight(GLuint ambient_intensity_location, GLuint ambient_color_location,
        GLuint direction_location, GLuint diffuse_intensity_location)
{
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
    glUniform3f(direction_location, direction.x, direction.y, direction.z);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);
}

Light::~Light()
{
}

