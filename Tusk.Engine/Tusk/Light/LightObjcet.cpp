#include "tuskpch.h"

#include "Tusk/Renderer/RenderCommand.h"
#include "LightObject.h"

namespace Tusk {

	LightObject::LightObject() {
		Logger::Log("Light created");
		_shader = CreateRef<LightShader>();
		generateLightCubeBuffers();
	}

	void LightObject::draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& transform) {
		_shader->setShaderUniforms(projection, view, transform);
		_vertexArray->bind();
		RenderCommand::drawIndexed(_vertexArray);
		_vertexArray->unbind();
	}

	void LightObject::generateLightCubeBuffers() {
		_vertexArray = VertexArray::create();

		std::vector<Vertex> vertices = {
			Vertex{glm::vec3{0.1f, -0.1f, -0.1f}},
			Vertex{glm::vec3{0.1f, -0.1f, 0.1f}},
			Vertex{glm::vec3{-0.1f, -0.1f, 0.1f}},
			Vertex{glm::vec3{-0.1f, -0.1f, -0.1f}},
			Vertex{glm::vec3{0.1f, 0.1f, -0.1f}},
			Vertex{glm::vec3{0.1f, 0.1f, 0.1f}},
			Vertex{glm::vec3{-0.1f, 0.1f, 0.1f}},
			Vertex{glm::vec3{-0.1f, 0.1f, -0.1f}},
		};

		std::vector<uint32_t> indices = {
			1, 2, 3, 7, 6, 5, 4, 5, 1,
			5, 6, 2, 2, 6, 7, 0, 3, 7,
			0, 1, 3, 4, 7, 5, 0, 4, 1,
			1, 5, 2, 3, 2, 7, 4, 0, 7
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices);

		_vertexArray->setVertexBuffer(vertexBuffer);
		_vertexArray->setIndexBuffer(indexBuffer);
	}
}