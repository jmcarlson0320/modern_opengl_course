#ifndef NO_COMPILE

#include "Mesh.h"
#include "load_obj.h"

Mesh::Mesh()
{
    vbo = new VertexBuffer();
    ibo = new IndexBuffer();
    vao = new VertexArray();
}

void Mesh::loadObj(char *filename)
{
    // load obj file contents into vertex buffer and index buffer
    MeshData meshData = load_obj(filename);
    vbo->init(meshData.vertices.data(), meshData.vertices.size());
    ibo->init(meshData.indices.data(), meshData.indices.size());

    // define the vertex layout
    BufferLayout layout;
    layout.addElem(FLOAT, 3); // position
    layout.addElem(FLOAT, 3); // normal
    layout.addElem(FLOAT, 2); // texture coordinate
    vbo->setLayout(layout);

    // assemble the vertex array object
    vao->addVertexBuffer(vbo);
    vao->addIndexBuffer(ibo);
}

VertexBuffer *Mesh::getVertexBuffer()
{
    return vbo;
}

VertexArray *Mesh::getVertexArray()
{
    return vao;
}

IndexBuffer *Mesh::getIndexBuffer()
{
    return ibo;
}

#endif // NO_COMPILE