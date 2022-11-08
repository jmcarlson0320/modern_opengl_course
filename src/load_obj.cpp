#include "load_obj.h"

#include <string>
#include <vector>
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

static tinyobj::ObjReader create_reader(const char *filename)
{
    std::string inputfile(filename);
    tinyobj::ObjReaderConfig reader_config;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    return reader;
}

MeshData load_obj(const char *filename)
{
    tinyobj::ObjReader reader = create_reader(filename);

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    auto& vertex_data = attrib.vertices;
    auto& normal_data = attrib.normals;
    auto& texture_data = attrib.texcoords;

    MeshData meshData;

    meshData.layout.addElem(FLOAT, 3);      // position
    if (normal_data.size() > 0)
        meshData.layout.addElem(FLOAT, 3);  // normal
        /*
    if (texture_data.size() > 0)
        meshData.layout.addElem(FLOAT, 2);  // texcoord
        */

    int index_count = 0;
    for (int s = 0; s < shapes.size(); s++) {
        auto &shape_data = shapes[s].mesh.indices;
        for (int i = 0; i < shape_data.size(); i++) {
            auto idx = shape_data[i];
            int v = idx.vertex_index;
            meshData.vertices.push_back(vertex_data[3 * v + 0]);
            meshData.vertices.push_back(vertex_data[3 * v + 1]);
            meshData.vertices.push_back(vertex_data[3 * v + 2]);

            int n = idx.normal_index;
            if (n >= 0) {
                meshData.vertices.push_back(normal_data[3 * n + 0]);
                meshData.vertices.push_back(normal_data[3 * n + 1]);
                meshData.vertices.push_back(normal_data[3 * n + 2]);
            }

/*
            int t = idx.texcoord_index;
            if (t >= 0) {
                meshData.vertices.push_back(texture_data[2 * t + 0]);
                meshData.vertices.push_back(texture_data[2 * t + 1]);
            }
            */

            meshData.indices.push_back(index_count);
            index_count++;
        }
    }

    return meshData;
}