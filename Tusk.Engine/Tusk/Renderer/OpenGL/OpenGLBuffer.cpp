#include "tuskpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Tusk {

	OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<Vertex> vertices) {
		glCreateBuffers(1, &_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &_rendererID);
	}

	void OpenGLVertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	}

	void OpenGLVertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector <uint32_t> indices) {
		_count = (uint32_t) indices.size();
		glCreateBuffers(1, &_rendererID); 
		glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
		glBufferData(GL_ARRAY_BUFFER, _count * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &_rendererID);
	}

	void OpenGLIndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
	}

	void OpenGLIndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
