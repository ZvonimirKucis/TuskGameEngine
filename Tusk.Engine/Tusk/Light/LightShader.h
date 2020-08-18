#pragma once

#include "Tusk/Renderer/Shader.h"

namespace Tusk {

	class LightShader {
	public:
		LightShader();

		void setShaderUniforms(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& transform);

	private:
		void compileShader();

	private:
		Ref<Shader> _shader;
	};

}