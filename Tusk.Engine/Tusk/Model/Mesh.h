#pragma once

#include "Tusk/Renderer/Buffer.h"
#include "Tusk/Renderer/VertexArray.h"
#include "Tusk/Renderer/Shader.h"
#include "Tusk/Renderer/Texture.h"

namespace Tusk {

	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture2D>> textures);
		~Mesh();

		void draw(Ref<Shader> shader);

	private:
		void setupMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	private:
		std::vector<Vertex> _vertices;
		Ref<VertexArray> _vertexArray;

		std::vector<Ref<Texture2D>> _textures;

		friend class Model;
	};

}