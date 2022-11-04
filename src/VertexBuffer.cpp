#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer()
    : bufferID(0)
{
    // using initializer lists
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::init(float *data, unsigned int num_elem)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, num_elem * sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout(BufferLayout layout)
{
    this->layout = layout;
}

BufferLayout VertexBuffer::getLayout()
{
    return layout;
}
