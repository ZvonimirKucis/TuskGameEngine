#include "tuskpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Vulkan/VulkanBuffer.h"

namespace Tusk {

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
		return CreateRef<VulkanVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size) {
		return CreateRef<VulkanIndexBuffer>(indices, size);
	}
}