#pragma once

#include "Tusk/Renderer/Buffer.h"

namespace Tusk {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(std::vector<Vertex> vertices);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

	private:
		uint32_t _rendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(std::vector <uint32_t> indices);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t getCount() const override { return _count; }
	private:
		uint32_t _rendererID;
		uint32_t _count;
	};

}