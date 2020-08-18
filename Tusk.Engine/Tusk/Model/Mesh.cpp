#include "tuskpch.h"

#include "Mesh.h"
#include "Tusk/Renderer/RenderCommand.h"1


namespace Tusk {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture2D>> textures)
		:_textures(textures) {
		setupMesh(vertices, indices);

        vertices.clear();
        indices.clear();
	}

	void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
		_vertexArray = VertexArray::create();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices);

		_vertexArray->setVertexBuffer(vertexBuffer);
		_vertexArray->setIndexBuffer(indexBuffer);

	}

	void Mesh::draw(Ref<Shader> shader) {
        uint32_t diffuseNr = 1;
        uint32_t specularNr = 1;
        uint32_t normalNr = 1;
        uint32_t heightNr = 1;
        for (uint32_t i = 0; i < _textures.size(); i++) {
            std::string number;
            std::string name = Texture::toString(_textures[i]->getType());
            
            switch (_textures[i]->getType()) {
                case TextureType::Diffuse:
                    number = std::to_string(diffuseNr++);
                    break;
                case TextureType::Specular:
                    number = std::to_string(specularNr++);
                    break;
                case TextureType::Normal:
                    number = std::to_string(normalNr++);
                    break;
                case TextureType::Height:
                    number = std::to_string(heightNr++);
                    break;
            }
            shader->setInt((name + number).c_str(), i);
            _textures[i]->bind(i);
        }

		_vertexArray->bind();
		RenderCommand::drawIndexed(_vertexArray);
		_vertexArray->unbind();
	}

	Mesh::~Mesh() {
	}

}