#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>

class Material {
    public:
        Material();
        Material(GLfloat specular_intensity, GLfloat shininess);

        void UseMaterial(GLuint spec_intensity_location, GLuint shininess_location);

        ~Material();

        GLfloat specular_intensity;
        GLfloat shininess;

};

#endif // MATERIAL_H
