#pragma once

#include "Tusk/Renderer/Buffer.h"
#include "Tusk/Renderer/VertexArray.h"

namespace Tusk {

	class Mesh {
	public:
		Mesh() = default;
		Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
		~Mesh();

		void draw();

	private:
		void setupMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	private:
		Ref<VertexArray> _vertexArray;

		friend class Model;
	};

}