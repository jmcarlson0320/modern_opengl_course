#include "VertexArray.h"
#include "VertexBuffer.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vertexArrayID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vertexArrayID);
}

void VertexArray::bind()
{
    glBindVertexArray(vertexArrayID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(VertexBuffer *vertexBuffer)
{
    // load vertices
    bind();
    vertexBuffer->bind();
    BufferLayout layout = vertexBuffer->getLayout();
    std::vector<LayoutElem> elements = layout.getElements();
    for (long unsigned int i = 0; i < elements.size(); i++) {
        LayoutElem cur_elem = elements[i];
        glVertexAttribPointer((unsigned int) i, cur_elem.count, GL_FLOAT, GL_FALSE, layout.getStride(), (const void *) cur_elem.offset);
        glEnableVertexAttribArray(i);

    }

    vertexBuffer->unbind();
    unbind();
}

void VertexArray::addIndexBuffer(IndexBuffer *indexBuffer)
{
    bind();
    indexBuffer->bind();
    unbind();
}