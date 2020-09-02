#include "tuskpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Tusk {
	OpenGLVertexArray::OpenGLVertexArray(){
		glCreateVertexArrays(1, &_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &_rendererID);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(_rendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(_rendererID);
		vertexBuffer->bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		
		glEnableVertexAttribArray(4);
		glVertexAttribIPointer(4, 3, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, jointIndices));
		
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(_rendererID);
		indexBuffer->bind();

		_indexBuffer = indexBuffer;
		glBindVertexArray(0);
	}

}
