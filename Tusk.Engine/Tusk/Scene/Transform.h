#pragma once

#include <glm/glm.hpp>

namespace Tusk {

	class Transform {
	public:
		Transform() {
			/*recalculatePositionMatrix();
			recalculateRotationMatrix();
			recalculateScaleMatrix();*/
		}

		/*glm::vec3 getPosition() { return _position; }
		float getX() { return _position.x; }
		float getY() { return _position.y; }
		float getZ() { return _position.z; }

		void setPosition(glm::vec3 position) { _position = position; recalculatePositionMatrix(); }
		void setX(float value) { _position.x = value; recalculatePositionMatrix; }
		void setY(float value) { _position.y = value; recalculatePositionMatrix; }
		void setZ(float value) { _position.z = value; recalculatePositionMatrix; }

		glm::vec3 getScale() { return _scale; }
		float getScaleX() { return _scale.x; }
		float getScaleY() { return _scale.y; }
		float getScaleZ() { return _scale.z; }

		void setScale(glm::vec3 scale) { _scale = scale; recalculateScaleMatrix(); }
		void setScaleX(float value) { _scale.x = value; recalculateScaleMatrix; }
		void setScaleY(float value) { _scale.y = value; recalculateScaleMatrix; }
		void setScaleZ(float value) { _scale.z = value; recalculateScaleMatrix; }*/


		glm::mat4 getTransformMatrix() { return _positionMatrix * _rotationMatrix * _scaleMatrix; };

	private:
		/*void recalculatePositionMatrix() {
			_positionMatrix = glm::translate(glm::mat4{ 1.0f }, _position);
		}

		void recalculateScaleMatrix() {
			_scaleMatrix = glm::scale(glm::mat4{ 1.0f }, _scale);
		}

		void recalculateRotationMatrix() {
			_rotationMatrix = glm::rotate(glm::mat4{ 1.0f }, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			_rotationMatrix = glm::rotate(_rotationMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			_rotationMatrix = glm::rotate(_rotationMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		}*/

	private:
		glm::vec3 _position{0.0f};
		glm::vec3 _rotation{0.0f};
		glm::vec3 _scale{1.0f};

		glm::mat4 _positionMatrix;
		glm::mat4 _rotationMatrix;
		glm::mat4 _scaleMatrix;
	};
}