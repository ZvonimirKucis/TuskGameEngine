#include "tuskpch.h"
#include "VulkanBuffer.h"

#include <vulkan/vulkan.h>

namespace Tusk{

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size) {

	}

	VulkanVertexBuffer::~VulkanVertexBuffer() {

	}

	void VulkanVertexBuffer::bind() const {

	}

	void VulkanVertexBuffer::unbind() const {

	}



	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count) {
		_count = count;
	}

	VulkanIndexBuffer::~VulkanIndexBuffer() {

	}

	void VulkanIndexBuffer::bind() const {

	}

	void VulkanIndexBuffer::unbind() const {

	}

}