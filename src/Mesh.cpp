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
    // allocate buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    // allocate vaos
    glGenVertexArrays(1, &VAO);

    // load vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO);

        // define vertex attributes
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // position
            glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 11, 0);
            glEnableVertexAttribArray(V_POSITION);

            // normal
            glVertexAttribPointer(V_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 11, (void *) (sizeof(vertex_data[0]) * 3));
            glEnableVertexAttribArray(V_NORMAL);

            // color
            glVertexAttribPointer(V_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 11, (void *) (sizeof(vertex_data[0]) * 6));
            glEnableVertexAttribArray(V_COLOR);

            // texture coordinates
            glVertexAttribPointer(V_TEXCOOR, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 11, (void *) (sizeof(vertex_data[0]) * 9));
            glEnableVertexAttribArray(V_TEXCOOR);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind vao
    glBindVertexArray(0);


    // load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * index_count, &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    this->index_count = index_count;

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
