#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "stb_image.h"

class Texture {
    public:
        Texture();
        Texture(char *fileLocation);

        void load();
        void use();
        void clear();

        ~Texture();

    private:
        GLuint textureID;
        int width;
        int height;
        int bitDepth;
        char *fileLocation;
};

#endif // TEXTURE_H
