#include "tuskpch.h"

#include "Skybox.h"
#include "Tusk/Renderer/RenderCommand.h"

namespace Tusk {

	char* skyboxVertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;

			out vec3 TexCoords;
			
			uniform mat4 view;
			uniform mat4 projection;
			
			void main()
			{
				TexCoords = aPos;
				vec4 pos = projection * view * vec4(aPos, 1.0);
				gl_Position = pos.xyww;
			}
		)";

	char* skyboxFragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;
			
			in vec3 TexCoords;
			
			uniform samplerCube skybox;
			
			void main()
			{
			    FragColor = texture(skybox, TexCoords);
			}
		)";

	Skybox::Skybox(const std::vector<std::string> faces) {
		_cubemapTexture = Cubemap::create(faces);
		_skyboxShader = Shader::compile(skyboxVertexSrc, skyboxFragmentSrc);

		loadBuffer();
	}

	void Skybox::draw(const glm::mat4& projection, const glm::mat4& view) {
		_skyboxShader->bind();
		_skyboxShader->setMat4("projection", projection);
		_skyboxShader->setMat4("view", view);
		
		_skyboxBuffer->bind();
		_cubemapTexture->bind();
		RenderCommand::drawIndexed(_skyboxBuffer);
		_skyboxBuffer->unbind();
	}

	void Skybox::loadBuffer() {
		_skyboxBuffer = VertexArray::create();

		std::vector<Vertex> vertices = {
			Vertex{glm::vec3{1, -1, -1}},
			Vertex{glm::vec3{1, -1, 1}},
			Vertex{glm::vec3{-1, -1, 1}},
			Vertex{glm::vec3{-1, -1, -1}},
			Vertex{glm::vec3{1, 1, -1}},
			Vertex{glm::vec3{1, 1, 1}},
			Vertex{glm::vec3{-1, 1, 1}},
			Vertex{glm::vec3{-1, 1, -1}},
		};

		std::vector<uint32_t> indices = {
			1, 2, 3, 7, 6, 5, 4, 5, 1,
			5, 6, 2, 2, 6, 7, 0, 3, 7,
			0, 1, 3, 4, 7, 5, 0, 4, 1,
			1, 5, 2, 3, 2, 7, 4, 0, 7
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices);

		_skyboxBuffer->setVertexBuffer(vertexBuffer);
		_skyboxBuffer->setIndexBuffer(indexBuffer);
	}
}