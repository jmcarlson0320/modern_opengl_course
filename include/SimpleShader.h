#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class SimpleShader
{
    public:
        SimpleShader();
        ~SimpleShader();

        void fromFile(const char *vertFilename, const char *fragFilename);

        void use();
        void clear();

        void setUniformFloat(char *name, float value);
        void setUniformVec3(char *name, glm::vec3 value);
        void setUniformMat4(char *name, glm::mat4 value);

    private:
        GLuint programID;
};

#endif // SIMPLESHADER_H
