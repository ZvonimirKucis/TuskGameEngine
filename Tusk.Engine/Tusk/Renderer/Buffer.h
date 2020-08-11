#pragma once

#include <vulkan/vulkan.h>
#include "Vulkan/VulkanVertex.h"

namespace Tusk {
	class VulkanDevice;
	class VulkanCommand;

	enum class ShaderDataType {
		None = 0, 
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t shaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::Float:  return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Int:    return 4;
			case ShaderDataType::Int2:   return 4 * 2;
			case ShaderDataType::Int3:   return 4 * 3;
			case ShaderDataType::Int4:   return 4 * 4;
			case ShaderDataType::Mat3:   return 4 * 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4 * 4;
			case ShaderDataType::Bool:   return 1;
		}
		return 0;
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name)
			: name(name), type(type), size(shaderDataTypeSize(type)), offset(0) 
		{
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: _elements(elements)
		{
			calculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement> getElements() { return _elements;  }

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }

	private:
		void calculateOffsetsAndStride() {
			uint32_t offset = 0;
			_stride = 0;
			for (auto& element : _elements) {
				element.offset = offset;
				offset += element.size;
				_stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> _elements;
		uint32_t _stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual VkBuffer getBuffer() = 0;
		virtual VkDeviceMemory getMemory() = 0;

		virtual void bind(VulkanDevice* device, VulkanCommand* command) = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;

		static Ref<VertexBuffer> create(std::vector <Vertex> vertices);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void bind(VulkanDevice* device, VulkanCommand* command) = 0;
		virtual void unbind() const = 0;

		virtual VkBuffer getBuffer() = 0;
		virtual VkDeviceMemory getMemory() = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IndexBuffer> create(std::vector<uint32_t> indices);
	};
}