#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
    public:
        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();

        void addVertexBuffer(VertexBuffer *vertexBuffer);
        void addIndexBuffer(IndexBuffer *indexBuffer);

    private:
        GLuint vertexArrayID;
        int indexCount;
};

#endif // VERTEXARRAY_H
