#include "tuskpch.h"
#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace Tusk {
	Ref<Shader> Shader::create(const std::string& vertexPath, const std::string& fragmentPath) {
		return CreateRef<OpenGLShader>(vertexPath, fragmentPath);
	}
}