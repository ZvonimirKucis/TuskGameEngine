#include "tuskpch.h"

#include "LightShader.h"

namespace Tusk {

	char* vertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			
			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			
			void main()
			{
				gl_Position = projection * view * model * vec4(aPos, 1.0);
			}
		)";

	char* fragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;
			
			void main()
			{
			    FragColor = vec4(1.0); // set all 4 vector values to 1.0
			}
		)";

	LightShader::LightShader() {
		compileShader();
	}

	void LightShader::compileShader() {
		_shader = Shader::compile(vertexSrc, fragmentSrc);
	}

	void LightShader::setShaderUniforms(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& transform) {
		_shader->bind();
		_shader->setMat4("projection", projection);
		_shader->setMat4("view", view);
		_shader->setMat4("model", transform);
	}

}