#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	class Transform {
	public:
		Transform(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
			: _position(position), _rotation(rotation), _scale(scale) {
			recalculateModelMatrix();
		}

		glm::vec3 getPositon() { return _position; }
		glm::vec3 getRotation() { return _rotation; }
		glm::vec3 getScale() { return _scale; }

		void setPosition(const glm::vec3& value) { _position = value; recalculateModelMatrix(); }
		void setRotation(const glm::vec3& value) { _rotation = value; clampRotation(); recalculateModelMatrix(); }

		void setScale(float value) { _scale = glm::vec3(value); recalculateModelMatrix(); }
		void setScale(const glm::vec3& value) { _scale = value; recalculateModelMatrix(); }

		glm::mat4 getModelMatrix() {
			return _modelMatrix;
		}

	private:
		void clampRotation() {
			_rotation.x = glm::abs(_rotation.x) > 360 ? glm::abs(_rotation.x) - 360 : _rotation.x;
			_rotation.y = glm::abs(_rotation.y) > 360 ? glm::abs(_rotation.y) - 360 : _rotation.y;
			_rotation.z = glm::abs(_rotation.z) > 360 ? glm::abs(_rotation.z) - 360 : _rotation.z;
		}

		void recalculateModelMatrix() {
			glm::mat4 modelMatrix = glm::mat4(1.0f);

			modelMatrix = glm::translate(modelMatrix, _position);

			modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));

			_modelMatrix = glm::scale(modelMatrix, _scale);
		}

	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _modelMatrix;
	};
}