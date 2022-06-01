#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
    public:
        IndexBuffer(unsigned int *data, unsigned int num_elem);
        ~IndexBuffer();

        void bind();
        void unbind();

    private:
        GLuint bufferID;
};

#endif // INDEXBUFFER_H
