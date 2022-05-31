#include "Light.h"

Light::Light()
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_amount = 1.0f;
    intensity = 1.0f;
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambient_amount, GLfloat intensity, glm::vec3 position)
{
    this->color = glm::vec3(r, g, b);
    this->ambient_amount = ambient_amount;
    this->intensity = intensity;
    this->position = position;
}

Light::~Light()
{
}

