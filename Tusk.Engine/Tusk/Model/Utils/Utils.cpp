#include "tuskpch.h"

#include "Utils.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {
	glm::mat4 Utils::correction = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1, 0, 0));

	std::vector<std::string> Utils::split(const std::string& str, const char delim) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string item;

		while (getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	std::string Utils::trim(const std::string& str)
	{
		size_t first = str.find_first_not_of(' ');
		if (std::string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}

	glm::quat Utils::quaternionFromMatrix(const glm::mat4& matrix) {
		float x, y, z, w;
		float diagonal = matrix[0][0] + matrix[1][1] + matrix [2][2];

		if (diagonal > 0) {
			float w4 = (float)(glm::sqrt(diagonal + 1.0f) * 2.0f);
			w = w4 / 4.0f;
			x = (matrix[2][1] - matrix[1][2]) / w4;
			y = (matrix[0][2] - matrix[2][0]) / w4;
			z = (matrix[1][0] - matrix[0][1]) / w4;
		}
		else if ((matrix[0][0] > matrix[1][1]) && (matrix[0][0] > matrix[2][2])) {
			float x4 = (float)(glm::sqrt(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]) * 2.0f);
			w = (matrix[2][1] - matrix[1][2]) / x4;
			x = x4 / 4.0f;
			y = (matrix[0][1] + matrix[1][0]) / x4;
			z = (matrix[0][2] + matrix[2][0]) / x4;
		}
		else if (matrix[1][1] > matrix[2][2]) {
			float y4 = (float)(glm::sqrt(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 2.0f);
			w = (matrix[0][2] - matrix[2][0]) / y4;
			x = (matrix[0][1] + matrix[1][0]) / y4;
			y = y4 / 4.0f;
			z = (matrix[1][2] + matrix[2][1]) / y4;
		}
		else {
			float z4 = (float)(glm::sqrt(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 2.0f);
			w = (matrix[1][0] - matrix[0][1]) / z4;
			x = (matrix[0][2] + matrix[2][0]) / z4;
			y = (matrix[1][2] + matrix[2][1]) / z4;
			z = z4 / 4.0f;
		}

		return glm::quat(w, x, y, z);
	}

	void Utils::calculateTangentSpace(std::vector<Vertex>& vertices) {
		for (uint32_t i = 0; i < vertices.size(); i += 3) {
			Vertex v0 = vertices[i];
			Vertex v1 = vertices[i + 1];
			Vertex v2 = vertices[i + 2];

			glm::vec3 deltaPos1 = v1.position - v0.position;
			glm::vec3 deltaPos2 = v2.position - v0.position;

			glm::vec2 deltaUV1 = v1.texCoords - v0.texCoords;
			glm::vec2 deltaUV2 = v2.texCoords - v0.texCoords;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

			vertices[i].tangent = tangent;
			vertices[i + 1].tangent = tangent;
			vertices[i + 2].tangent = tangent;
		}
	}
}