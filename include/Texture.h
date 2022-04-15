#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture {
    public:
        Texture();
        ~Texture();

        void fromFile(const char *imageFilename);

        void use();
        void clear();

    private:
        GLuint textureID;
        int width;
        int height;
        int bitDepth;
};

#endif // TEXTURE_H
