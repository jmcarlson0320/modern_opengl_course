#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

typedef struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    BufferLayout layout;
} MeshData;

class Mesh {
    public:
        Mesh();
        ~Mesh();

        void loadObj(char *filename);

        VertexBuffer *getVertexBuffer();
        IndexBuffer *getIndexBuffer();
        VertexArray *getVertexArray();

    private:
        MeshData meshData;
        VertexBuffer *vbo;
        IndexBuffer *ibo;
        VertexArray *vao;
};

#endif // MESH_H