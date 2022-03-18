#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

enum vertex_attributes {
    V_POSITION,
    NUM_ATTRIBUTES
};

class Mesh {
    public:
        Mesh();
        Mesh(glm::vec3 *vertices, GLuint num_vertices, GLuint *indices, GLuint num_indices);
        void render();
        ~Mesh();
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

        GLuint num_indices;
};

#endif // MESH_H
