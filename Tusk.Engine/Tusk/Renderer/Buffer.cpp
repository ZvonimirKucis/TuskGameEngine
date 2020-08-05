#include "tuskpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Vulkan/VulkanBuffer.h"

namespace Tusk {

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) 
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::Vulkan:
				return CreateRef<VulkanVertexBuffer>(vertices, size);
		}

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size) {
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::Vulkan :
				return CreateRef<VulkanIndexBuffer>(indices, size);
		}

		return nullptr;
	}
}