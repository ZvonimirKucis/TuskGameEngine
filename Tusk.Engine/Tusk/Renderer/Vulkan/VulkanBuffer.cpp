#include "tuskpch.h"
#include "VulkanBuffer.h"
#include "VulkanUtils.h"

namespace Tusk{

	VulkanVertexBuffer::VulkanVertexBuffer(std::vector <Vertex> vertices) {
		_vertices = vertices;
	}

	VulkanVertexBuffer::~VulkanVertexBuffer() {
		
	}

	void VulkanVertexBuffer::bind(VulkanDevice* device) {
		if (_vertexBuffer == VK_NULL_HANDLE) {
			_device = device;
			VkBufferCreateInfo bufferInfo{};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = sizeof(_vertices[0]) * _vertices.size();
			bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			VK_CHECK(vkCreateBuffer(_device->getDevice(), &bufferInfo, nullptr, &_vertexBuffer))

				VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(_device->getDevice(), _vertexBuffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			VK_CHECK(vkAllocateMemory(_device->getDevice(), &allocInfo, nullptr, &_vertexBufferMemory))

				vkBindBufferMemory(_device->getDevice(), _vertexBuffer, _vertexBufferMemory, 0);

			void* data;
			vkMapMemory(_device->getDevice(), _vertexBufferMemory, 0, bufferInfo.size, 0, &data);
			memcpy(data, _vertices.data(), (size_t)bufferInfo.size);
			vkUnmapMemory(_device->getDevice(), _vertexBufferMemory);
		}	
	}

	uint32_t VulkanVertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(_device->getPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		throw std::runtime_error("failed to find suitable memory type!");
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