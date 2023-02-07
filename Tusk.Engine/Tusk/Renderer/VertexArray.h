#pragma once

#include "Buffer.h"

namespace Tusk {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const Ref<VertexBuffer>& getVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

		static Ref<VertexArray> create();
	};

}
