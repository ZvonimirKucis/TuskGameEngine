#include "tuskpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

namespace Tusk {

	Ref<Shader> Shader::Create(const std::string& filepath) {
		 return CreateRef<OpenGLShader>(filepath);
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}

}