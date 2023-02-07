#pragma once

#include <glm/glm.hpp>

#include "LightShader.h"
#include "Tusk/Renderer/Buffer.h"
#include "Tusk/Renderer/VertexArray.h"


namespace Tusk {
	
	class LightObject {
	public:
		LightObject();

		void draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& transform = glm::mat4{ 1.0f });

	private:
		void generateLightCubeBuffers();
	private:
		Ref<LightShader> _shader;
		Ref<VertexArray> _vertexArray;
	};
}