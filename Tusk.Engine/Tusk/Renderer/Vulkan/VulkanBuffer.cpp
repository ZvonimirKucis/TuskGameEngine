#include "tuskpch.h"
#include "../../Utils/Logger.h"
#include "VulkanBuffer.h"
#include "VulkanUtils.h"

namespace Tusk{

	VulkanVertexBuffer::VulkanVertexBuffer(std::vector <Vertex> vertices) {
		_vertices = vertices;
	}

	VulkanVertexBuffer::~VulkanVertexBuffer() {
		
	}

	void VulkanVertexBuffer::bind(VulkanDevice* device, VulkanCommand* command) {
		if (_vertexBuffer == VK_NULL_HANDLE) {
			_device = device;
			_command = command;
			
			VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

			VkBuffer stagingBuffer;
			VkDeviceMemory stagingBufferMemory;
			VulkanBufferHelper::createBuffer(_device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

			void* data;
			vkMapMemory(_device->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, _vertices.data(), (size_t)bufferSize);
			vkUnmapMemory(_device->getDevice(), stagingBufferMemory);

			VulkanBufferHelper::createBuffer(_device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);

			VulkanBufferHelper::copyBuffer(_device, _command, stagingBuffer, _vertexBuffer, bufferSize);

			vkDestroyBuffer(_device->getDevice(), stagingBuffer, nullptr);
			vkFreeMemory(_device->getDevice(), stagingBufferMemory, nullptr);
		}	
	}

	void VulkanVertexBuffer::unbind() const {

	}



	VulkanIndexBuffer::VulkanIndexBuffer(std::vector<uint32_t> indices) {
		_indices = indices;
	}

	VulkanIndexBuffer::~VulkanIndexBuffer() {

	}

	void VulkanIndexBuffer::bind(VulkanDevice* device, VulkanCommand* command) {
		if (_indexBuffer == VK_NULL_HANDLE) {
			_device = device;
			_command = command;

			VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

			VkBuffer stagingBuffer;
			VkDeviceMemory stagingBufferMemory;
			VulkanBufferHelper::createBuffer(_device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

			void* data;
			vkMapMemory(_device->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, _indices.data(), (size_t)bufferSize);
			vkUnmapMemory(_device->getDevice(), stagingBufferMemory);

			VulkanBufferHelper::createBuffer(_device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

			VulkanBufferHelper::copyBuffer(_device, _command, stagingBuffer, _indexBuffer, bufferSize);

			vkDestroyBuffer(_device->getDevice(), stagingBuffer, nullptr);
			vkFreeMemory(_device->getDevice(), stagingBufferMemory, nullptr);
		}
	}


	void VulkanIndexBuffer::unbind() const {

	}






	void VulkanBufferHelper::createBuffer(VulkanDevice* device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VK_CHECK(vkCreateBuffer(device->getDevice(), &bufferInfo, nullptr, &buffer))

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device->getDevice(), buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(device, memRequirements.memoryTypeBits, properties);

		VK_CHECK(vkAllocateMemory(device->getDevice(), &allocInfo, nullptr, &bufferMemory))

		vkBindBufferMemory(device->getDevice(), buffer, bufferMemory, 0);
	}

	void VulkanBufferHelper::copyBuffer(VulkanDevice* device, VulkanCommand* command, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
		VkCommandBuffer commandBuffer = command->beginSingleTimeCommands();

		VkBufferCopy copyRegion{};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		command->endSingleTimeCommands(commandBuffer);
	}

	uint32_t VulkanBufferHelper::findMemoryType(VulkanDevice* device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		Logger::Fatal("Failed to find suitable memory type!");
	}

}