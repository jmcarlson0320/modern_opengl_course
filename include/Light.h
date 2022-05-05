#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambient_intensity);
    void UseLight(GLfloat ambient_intensity_location, GLfloat ambient_color_location);
    ~Light();

private:
    glm::vec3 color;
    GLfloat ambient_intensity;

};

#endif // LIGHT_H
