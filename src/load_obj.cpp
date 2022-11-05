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

    MeshData meshData;

    // create meshdata index array
    int index_count = 0;
    for (int s = 0; s < shapes.size(); s++) {
        std::cout << "number of indices: " << shapes[s].mesh.indices.size() << std::endl;
        for (int i = 0; i < shapes[s].mesh.indices.size(); i++) {
            auto idx = shapes[s].mesh.indices[i];
            auto v = idx.vertex_index;
            meshData.vertices.push_back(attrib.vertices[v]);
            meshData.vertices.push_back(attrib.vertices[v + 1]);
            meshData.vertices.push_back(attrib.vertices[v + 2]);

            auto n = idx.normal_index;
            if (n >= 0) {
                meshData.vertices.push_back(attrib.normals[n]);
                meshData.vertices.push_back(attrib.normals[n + 1]);
                meshData.vertices.push_back(attrib.normals[n + 2]);
            }

            auto t = idx.texcoord_index;
            if (t >= 0) {
                meshData.vertices.push_back(attrib.texcoords[t]);
                meshData.vertices.push_back(attrib.texcoords[t + 1]);
            }

            meshData.indices.push_back(index_count);
            index_count++;
        }
    }

    return meshData;
}