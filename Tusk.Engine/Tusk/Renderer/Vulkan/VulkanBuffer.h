#pragma once


#include <vulkan/vulkan.h>

#include "../Buffer.h"
#include "VulkanDevice.h"
#include "VulkanVertex.h"

namespace Tusk {

	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(std::vector <Vertex> vertices);
		virtual ~VulkanVertexBuffer();

		virtual void bind(VulkanDevice* device) override;
		virtual void unbind() const override;

		virtual VkBuffer getBuffer() override { return _vertexBuffer; };
		virtual VkDeviceMemory getMemory() override { return _vertexBufferMemory; }

		virtual void setLayout(const BufferLayout& layout) override { _layout = layout; }
		virtual const BufferLayout& getLayout() const override { return _layout; }

	private:
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	private:
		VulkanDevice* _device;
		VkBuffer _vertexBuffer = VK_NULL_HANDLE;
		VkDeviceMemory _vertexBufferMemory;

		std::vector <Vertex> _vertices;
		BufferLayout _layout;
	};

	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t getCount() const { return _count; }

	private:
		uint32_t _count;
	};
}