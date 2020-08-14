#include "tuskpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Vulkan/VulkanBuffer.h"

namespace Tusk {

	VertexBuffer* VertexBuffer::create(std::vector <Vertex> vertices) {
		return new VulkanVertexBuffer(vertices);
	}

	IndexBuffer* IndexBuffer::create(std::vector<uint32_t> indices) {
		return new VulkanIndexBuffer(indices);
	}
}