#pragma once


#include <vulkan/vulkan.h>

#include "../Buffer.h"
#include "VulkanDevice.h"
#include "VulkanVertex.h"
#include "VulkanCommand.h"

namespace Tusk {

	class VulkanBufferHelper {
	public:
		static void createBuffer(VulkanDevice* device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		static void copyBuffer(VulkanDevice* device, VulkanCommand* command, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		static uint32_t findMemoryType(VulkanDevice* device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};

	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(std::vector <Vertex> vertices);
		virtual ~VulkanVertexBuffer();

		virtual void bind(VulkanDevice* device, VulkanCommand* command) override;
		virtual void unbind() const override;

		virtual VkBuffer getBuffer() override { return _vertexBuffer; };
		virtual VkDeviceMemory getMemory() override { return _vertexBufferMemory; }

		virtual void setLayout(const BufferLayout& layout) override { _layout = layout; }
		virtual const BufferLayout& getLayout() const override { return _layout; }

	private:
		VulkanDevice* _device;
		VulkanCommand* _command;
		VkBuffer _vertexBuffer = VK_NULL_HANDLE;
		VkDeviceMemory _vertexBufferMemory;

		std::vector <Vertex> _vertices;
		BufferLayout _layout;
	};

	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(std::vector<uint32_t> indices);
		virtual ~VulkanIndexBuffer();

		virtual void bind(VulkanDevice* device, VulkanCommand* command) override;
		virtual void unbind() const override;

		virtual VkBuffer getBuffer() override { return _indexBuffer; };
		virtual VkDeviceMemory getMemory() override { return _indexBufferMemory; }

		virtual uint32_t getCount() const { return _indices.size(); }

	private:
		VulkanDevice* _device;
		VulkanCommand* _command;
		VkBuffer _indexBuffer = VK_NULL_HANDLE;
		VkDeviceMemory _indexBufferMemory;
		
		std::vector<uint32_t> _indices;
	};
}