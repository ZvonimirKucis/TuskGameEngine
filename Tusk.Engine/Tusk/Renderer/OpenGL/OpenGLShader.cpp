#include "tuskpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Tusk {

	void OpenGLShader::loadCode(const std::string& vertexPath, const std::string& fragmentPath) {
		std::string vertexCode = readFile(vertexPath);
		std::string fragmentCode = readFile(fragmentPath);

		compile(vertexCode, fragmentCode);
	}

	void OpenGLShader::compileCode(const std::string& vertexCode, const std::string& fragmentCode) {
		compile(vertexCode, fragmentCode);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(_rendererID);
	}

	std::string OpenGLShader::readFile(const std::string& filepath) {
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			} else {
				Logger::Fatal("Could not read from file: %s", filepath.c_str());
			}
		} else {
			Logger::Fatal("Could not open file: %s", filepath.c_str());
		}
		return result;
	}

	void OpenGLShader::compile(std::string vertexCode, std::string fragmentCode) {
		_rendererID = glCreateProgram();
		uint32_t vertex, fragment;
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glAttachShader(_rendererID, vertex);
		glAttachShader(_rendererID, fragment);
		glLinkProgram(_rendererID);
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void OpenGLShader::bind() const {
		glUseProgram(_rendererID);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::setInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::setIntArray(const std::string& name, int* values, uint32_t count) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::setFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}