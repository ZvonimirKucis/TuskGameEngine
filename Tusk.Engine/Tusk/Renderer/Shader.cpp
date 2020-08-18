#include "tuskpch.h"
#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace Tusk {
	Ref<Shader> Shader::load(const std::string& vertexPath, const std::string& fragmentPath) {
		Ref<Shader> shader = CreateRef<OpenGLShader>();
		shader->loadCode(vertexPath, fragmentPath);
		return shader;
	}

	Ref<Shader> Shader::compile(const std::string& vertexCode, const std::string& fragmentSrc) {
		Ref<Shader> shader = CreateRef<OpenGLShader>();
		shader->compileCode(vertexCode, fragmentSrc);
		return shader;
	}
}