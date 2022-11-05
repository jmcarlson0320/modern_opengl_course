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

    // interleave positions and normals
    // create meshdata vertex array
    for (int i = 0; i < attrib.vertices.size(); i += 3) {
        meshData.vertices.push_back(attrib.vertices[i]);
        meshData.vertices.push_back(attrib.vertices[i + 1]);
        meshData.vertices.push_back(attrib.vertices[i + 2]);
        meshData.vertices.push_back(attrib.normals[i]);
        meshData.vertices.push_back(attrib.normals[i + 1]);
        meshData.vertices.push_back(attrib.normals[i + 2]);
    }

    // create meshdata index array
    for (int s = 0; s < shapes.size(); s++) {
        for (int i = 0; i < shapes[s].mesh.indices.size(); i++) {
            meshData.indices.push_back(shapes[s].mesh.indices[i].vertex_index);
        }
    }

    return meshData;
}