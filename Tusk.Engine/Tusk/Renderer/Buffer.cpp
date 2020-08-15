#include "tuskpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace Tusk {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		  return CreateRef<OpenGLVertexBuffer>(size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

}