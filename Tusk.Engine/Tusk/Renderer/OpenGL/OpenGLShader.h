#pragma once

#include "Tusk/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Tusk {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader() {};
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void loadCode(const std::string& vertexPath, const std::string& fragmentPath)  override;
		virtual void compileCode(const std::string& vertexCode, const std::string& fragmentCode)  override;

		virtual void setInt(const std::string& name, int value) override;
		virtual void setIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void setFloat(const std::string& name, float value) override;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value) override;

	private:
		std::string readFile(const std::string& filepath);
		void compile(std::string vertexCode, std::string fragmentCode);
	private:
		uint32_t _rendererID;
	};

}