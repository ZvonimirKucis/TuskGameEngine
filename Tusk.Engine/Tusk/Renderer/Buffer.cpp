#include "tuskpch.h"
#include "Buffer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace Tusk {
	Ref<VertexBuffer> VertexBuffer::create(const std::vector<Vertex>& vertices) {
		return CreateRef<OpenGLVertexBuffer>(vertices);
	}

	Ref<IndexBuffer> IndexBuffer::create(const std::vector<uint32_t>& indices) {
		return CreateRef<OpenGLIndexBuffer>(indices);
	}
}