#pragma once

#include <string>

namespace Tusk {
	
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;

	private:
		uint32_t _rendererID;
	};
}