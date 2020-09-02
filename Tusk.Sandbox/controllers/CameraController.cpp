#include "CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {
	const float SENSITIVITY = 0.1f;
	const float SPEED = 15.0f;

	float lastX;
	float lastY;

	void CameraController::onCreate() {
		lastX = Input::getMouseX();
		lastY = Input::getMouseY();
	}

	void CameraController::onDestroy() {
	}

	void CameraController::onUpdate(float deltaTime) {
		auto& transform = getComponent<TransformComponent>().transform;
		auto pos = transform.getPosition();
		
		if (Input::isKeyPressed(TUSK_KEY_A))
			pos.x -= SPEED * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_D))
			pos.x += SPEED * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_W))
			pos.z -= SPEED * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_S))
			pos.z += SPEED * deltaTime;

		transform.setPosition(pos);

		float yaw = Input::getMouseX() - lastX;
		float pitch = lastY - Input::getMouseY();

		lastX = Input::getMouseX();
		lastY = Input::getMouseY();

		auto rot = transform.getRotation();
		
		rot.y -= yaw * SENSITIVITY;
		rot.x += pitch * SENSITIVITY;

		transform.setRotation(rot);

		/*auto rot = transform.getRotation();

		rot.y -= SPEED * deltaTime;

		transform.setRotation(rot);*/
	}
}