#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

enum VERTEX_ATTRIBUTES {
    V_POSITION,
    V_NORMAL,
    V_COLOR,
    V_TEXCOOR,
    NUM_ATTRIBUTES
};

class Mesh {
    public:
        Mesh();
        Mesh(GLfloat *vertex_data, GLuint vertex_data_size, GLuint *indices, GLuint index_count);
        void fromFile(const char *filename);
        void render();
        ~Mesh();
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

        GLuint index_count;
};

#endif // MESH_H
