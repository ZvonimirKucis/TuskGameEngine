#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Tusk/Renderer/Buffer.h"

namespace Tusk {
	class Utils {
	public:
		static std::vector<std::string> split(const std::string& s, const char delim);
		static glm::quat quaternionFromMatrix(const glm::mat4& matrix);
		static void calculateTangentSpace(std::vector<Vertex>& vertices);
		static std::string trim(const std::string& str);

		static glm::mat4 correction;
	};
}