#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Tusk {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setInt(const std::string& name, int value) = 0;
		virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;

		static Ref<Shader> create(const std::string& vertexPath, const std::string& fragmentPath);
	};

}