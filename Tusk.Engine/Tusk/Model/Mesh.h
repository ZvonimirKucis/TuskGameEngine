#pragma once

#include "../Renderer/Vulkan/VulkanVertex.h"
#include "../Renderer/Buffer.h"

namespace Tusk {

	class Mesh {
	public:
		Mesh(std::string modelPath);
		~Mesh();

		VertexBuffer* getVertexBuffer() { return _vertexBuffer; }
		IndexBuffer* getIndexBuffer() { return _indexBuffer; }

	private:
		void loadModel(std::string modelPath);
		void createBuffers();

	private:
		std::vector<Vertex> _vertices;
		std::vector<uint32_t> _indices;

		VertexBuffer* _vertexBuffer;
		IndexBuffer* _indexBuffer;
	};

}