#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>

class VertexBuffer
{
    public:
        VertexBuffer(float *data, unsigned int num_elem);
        ~VertexBuffer();

        void bind();
        void unbind();

    private:
        GLuint bufferID;
};

#endif // VERTEXBUFFER_H
