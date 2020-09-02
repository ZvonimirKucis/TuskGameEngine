#pragma once

#include "Tusk/Model/Mesh.h"
#include "VertexSkinData.h"
#include <glm/glm.hpp>
#include <pugixml.hpp>

namespace Tusk {
	class GeometryLoader {
	public:
		GeometryLoader(const pugi::xml_node& geometryNode);
		GeometryLoader(const pugi::xml_node& geometryNode, const std::vector<Ref<VertexSkin>>& vertexSkin);
		~GeometryLoader();

		Ref<Mesh> loadMesh();
		Ref<Mesh> loadAnimatedMesh();

	private:
		void extractMeshData();
		void extractAnimatedMeshData();

		std::vector<glm::vec3> readPositions();
		std::vector<glm::vec3> readNormals();
		std::vector<glm::vec2> readTextureCoords();

	private:
		pugi::xml_node _meshData;
		std::vector<Ref<VertexSkin>> _vertexSkin;

		std::vector<Vertex> _vertices;
		std::vector<uint32_t> _indices;
	};
}