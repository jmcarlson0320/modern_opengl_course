#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
    public:
        Shader();
        ~Shader();

        void fromFile(const char *vertFilename, const char *fragFilename);

        GLuint getModelLocation();
        GLuint getViewLocation();
        GLuint getProjectionLocation();
        GLuint getAmbientIntensityLocation();
        GLuint getAmbientColorLocation();
        GLuint getDiffuseIntensityLocation();
        GLuint getDirectionLocation();

        void use();
        void clear();

    private:
        GLuint shaderID;
        GLuint uniformModel;
        GLuint uniformView;
        GLuint uniformProjection;
        GLuint uniformAmbientIntensity;
        GLuint uniformAmbientColor;
        GLuint uniformDiffuseIntensity;
        GLuint uniformDirection;

};

#endif // SHADER_H
