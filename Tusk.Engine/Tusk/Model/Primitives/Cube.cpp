#include "tuskpch.h"

#include "Cube.h"

namespace Tusk {
	std::vector<Vertex> Cube::getVertices() {
		std::vector<Vertex> vertices = {
			Vertex{glm::vec3{1, -1, -1}},
			Vertex{glm::vec3{1, -1, 1}},
			Vertex{glm::vec3{-1, -1, 1}},
			Vertex{glm::vec3{-1, -1, -1}},
			Vertex{glm::vec3{1, 1, -1}},
			Vertex{glm::vec3{1, 1, 1}},
			Vertex{glm::vec3{-1, 1, 1}},
			Vertex{glm::vec3{-1, 1, -1}},
		};

		return vertices;
	}
	
	std::vector<uint32_t> Cube::getIndices() {
		std::vector<uint32_t> indices = {
			1, 2, 3, 7, 6, 5, 4, 5, 1,
			5, 6, 2, 2, 6, 7, 0, 3, 7,
			0, 1, 3, 4, 7, 5, 0, 4, 1,
			1, 5, 2, 3, 2, 7, 4, 0, 7
		};

		return indices;
	}
}