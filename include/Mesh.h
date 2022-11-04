#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh {
    public:
        Mesh();
        ~Mesh();

        void loadObj(char *filename);

        VertexArray getVertexArray();
        IndexBuffer getIndexBuffer();

    private:
        VertexBuffer vbo;
        IndexBuffer ibo;
        VertexArray vao;
};

#endif // MESH_H