#include "tuskpch.h"

#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny/tiny_obj_loader.h>


namespace Tusk {

	Mesh::Mesh(std::string modelPath) {
		loadModel(modelPath);
        createBuffers();
	}

	void Mesh::loadModel(std::string modelPath) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
            Logger::Fatal("Unable to load model data: %s", modelPath.c_str());
        }

        std::unordered_map<Vertex, uint32_t> uniqueVertices{};

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };

                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(_vertices.size());
                    _vertices.push_back(vertex);
                }
                _indices.push_back(uniqueVertices[vertex]);
            }
        }
	}

    void Mesh::createBuffers() {
        _vertexBuffer = VertexBuffer::create(_vertices);
        _indexBuffer = IndexBuffer::create(_indices);

        _vertices.clear();
        _indices.clear();
    }

	Mesh::~Mesh() {
        delete _vertexBuffer;
        delete _indexBuffer;
	}

}