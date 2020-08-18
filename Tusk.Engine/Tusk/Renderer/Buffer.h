#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Tusk {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Ref<VertexBuffer> create(const std::vector<Vertex>& vertices);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IndexBuffer> create(const std::vector<uint32_t>& indices);
	};

}