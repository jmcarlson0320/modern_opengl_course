#include <Mesh.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    num_indices = 0;
}

Mesh::Mesh(glm::vec3 *vertices, GLuint num_vertices, GLuint *indices, GLuint num_indices)
{
    // allocate vaos
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // allocate buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // load vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * num_vertices, &vertices[0], GL_STATIC_DRAW);

    // load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * num_indices, &indices[0], GL_STATIC_DRAW);
    this->num_indices = num_indices;

    // define vertex attributes
    glEnableVertexAttribArray(V_POSITION);
    glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

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
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
}
