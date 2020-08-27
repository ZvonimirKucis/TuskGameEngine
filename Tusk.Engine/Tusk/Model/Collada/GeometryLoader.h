#pragma once

#include "../Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <pugixml.hpp>

namespace Tusk {
	class GeometryLoader {
	public:
		GeometryLoader(pugi::xml_node geometryNode);
		~GeometryLoader();

		Ref<Mesh> loadMesh();
		void loadAnimatedMesh();

	private:
		void extractMeshData();
		std::vector<glm::vec3> readPositions();
		std::vector<glm::vec3> readNormals();
		std::vector<glm::vec2> readTextureCoords();

		std::vector<std::string> split(const std::string& s, const char delim);

	private:
		pugi::xml_node _meshData;

		std::vector<Vertex> _vertices;
		std::vector<uint32_t> _indices;

		glm::mat4 _correction = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0));
	};
}