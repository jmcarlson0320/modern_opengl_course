#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();

    Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambient_intensity,
            GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuse_intensity);

    void UseLight(GLuint ambient_intensity_location, GLuint ambient_color_location,
            GLuint direction_location, GLuint diffuse_intensity_location);
    ~Light();

private:
    glm::vec3 color;
    GLfloat ambient_intensity;

    glm::vec3 direction;
    GLfloat diffuse_intensity;

};

#endif // LIGHT_H
