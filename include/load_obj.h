#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>

#include "BufferLayout.h"

typedef struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    BufferLayout layout;
} MeshData;

MeshData load_obj(const char *filename);

#endif // LOAD_OBJ_H