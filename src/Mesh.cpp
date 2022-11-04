#ifndef NO_COMPILE

#include "Mesh.h"
#include "load_obj.h"

Mesh::Mesh()
{

}

void Mesh::loadObj(char *filename)
{
    // load obj file contents into vertex buffer and index buffer
    MeshData meshData = load_obj("resources/models/teapot.obj");
    vbo.init(meshData.vertices.data(), meshData.vertices.size());
    ibo.init(meshData.indices.data(), meshData.indices.size());

    // define the vertex layout
    BufferLayout layout;
    layout.addElem(FLOAT, 3); // position
    layout.addElem(FLOAT, 3); // normal
    vbo.setLayout(layout);

    // assemble the vertex array object
    vao.addVertexBuffer(&vbo);
    vao.addIndexBuffer(&ibo);
}

VertexArray Mesh::getVertexArray()
{
    return vao;
}

IndexBuffer Mesh::getIndexBuffer()
{
    return ibo;
}

#endif // NO_COMPILE