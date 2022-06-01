#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(unsigned int *data, unsigned int num_elem)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, num_elem * sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
