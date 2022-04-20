#include <Mesh.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    index_count = 0;
}

Mesh::Mesh(GLfloat *vertex_data, GLuint vertex_data_size, GLuint *indices, GLuint index_count)
{
    // allocate vaos
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // allocate buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // load vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

    // load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * index_count, &indices[0], GL_STATIC_DRAW);
    this->index_count = index_count;

    // define vertex attributes
    // position
    glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 5, 0);
    glEnableVertexAttribArray(V_POSITION);
    // texture coor
    glVertexAttribPointer(V_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 5, (void *) (sizeof(vertex_data[0]) * 3));
    glEnableVertexAttribArray(V_TEXTURE);

    // unbind vao and buffers - good practice
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::render()
{
    // render mesh
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
}
