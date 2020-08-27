#include "tuskpch.h"

#include "Mesh.h"
#include "Tusk/Renderer/RenderCommand.h"1


namespace Tusk {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices) {
		setupMesh(vertices, indices);
	}

	void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
		_vertexArray = VertexArray::create();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices);

		_vertexArray->setVertexBuffer(vertexBuffer);
		_vertexArray->setIndexBuffer(indexBuffer);

	}

	void Mesh::draw() {
		_vertexArray->bind();
		RenderCommand::drawIndexed(_vertexArray);
		_vertexArray->unbind();
	}

	Mesh::~Mesh() {
	}

}