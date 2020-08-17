#include "tuskpch.h"
#include "Buffer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace Tusk {
	Ref<VertexBuffer> VertexBuffer::create(std::vector<Vertex> vertices) {
		return CreateRef<OpenGLVertexBuffer>(vertices);
	}

	Ref<IndexBuffer> IndexBuffer::create(std::vector<uint32_t> indices) {
		return CreateRef<OpenGLIndexBuffer>(indices);
	}
}