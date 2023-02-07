#pragma once

#include "../VertexArray.h"

namespace Tusk {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const Ref<VertexBuffer>& getVertexBuffer() const override { return _vertexBuffer; }
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override  { return _indexBuffer; }
	private:
		uint32_t _rendererID;
		uint32_t m_VertexBufferIndex = 0;
		Ref<VertexBuffer> _vertexBuffer;
		Ref<IndexBuffer> _indexBuffer;
	};

}
