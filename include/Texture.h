#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture {
    public:
        Texture();
        Texture(const char *fileLocation);

        void use();
        void clear();

        ~Texture();

    private:
        GLuint textureID;
        int width;
        int height;
        int bitDepth;
};

#endif // TEXTURE_H
