#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();

    Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambient_amount, GLfloat intensity, glm::vec3 position);

    ~Light();

    glm::vec3 color;
    GLfloat ambient_amount;
    GLfloat intensity;
    glm::vec3 position;

};

#endif // LIGHT_H
