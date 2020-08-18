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
			Vertex{glm::vec3{0.0f, 0.0f, 0.0f}},
			Vertex{glm::vec3{0.0f, 0.0f, 1.0f}},
			Vertex{glm::vec3{1.0f, 0.0f, 0.0f}},
			Vertex{glm::vec3{1.0f, 0.0f, 1.0f}},
			Vertex{glm::vec3{1.0f, 1.0f, 0.0f}},
			Vertex{glm::vec3{1.0f, 1.0f, 1.0f}},
			Vertex{glm::vec3{0.0f, 1.0f, 0.0f}},
			Vertex{glm::vec3{0.0f, 1.0f, 1.0f}},
		};

		std::vector<uint32_t> indices = {
			1, 3, 2,
			3, 4, 2,
			3, 5, 4,
			5, 6, 4,
			5, 7, 6,
			7, 8, 6,
			7, 1, 8,
			1, 2, 8,
			1, 5, 3,
			1, 7, 5,
			2, 4, 6,
			2, 6, 8
		};


		Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices);

		_vertexArray->setVertexBuffer(vertexBuffer);
		_vertexArray->setIndexBuffer(indexBuffer);
	}
}