#pragma once

#include "Tusk/Renderer/Cubemap.h"
#include "Tusk/Renderer/Shader.h"
#include "Tusk/Renderer/VertexArray.h"

namespace Tusk {

	class Skybox {
	public:
		Skybox(const std::vector<std::string> faces);

		void draw(const glm::mat4& projection, const glm::mat4& view);

	private:
		void loadBuffer();

	private:
		Ref<Cubemap> _cubemapTexture;
		Ref<Shader> _skyboxShader;
		Ref<VertexArray> _skyboxBuffer;
	};

}
