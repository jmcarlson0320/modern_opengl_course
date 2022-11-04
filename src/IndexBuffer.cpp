#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer()
    : bufferID(0), num_indices(0)
{
    // using initializer lists
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::init(unsigned int *data, unsigned int num_elem)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_elem * sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    num_indices = num_elem;
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getIndexCount()
{
    return num_indices;
}

