#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>

#include "BufferLayout.h"

class VertexBuffer
{
    public:
        VertexBuffer();
        VertexBuffer(float *data, unsigned int num_elem);
        ~VertexBuffer();

        void bind();
        void unbind();

        void setLayout(BufferLayout layout);
        BufferLayout getLayout();

    private:
        GLuint bufferID;
        BufferLayout layout;
};

#endif // VERTEXBUFFER_H
