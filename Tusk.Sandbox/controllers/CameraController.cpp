#include "CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	void CameraController::onCreate() {
		auto& transform = getComponent<Tusk::TransformComponent>().transform;
		transform[3][2] = -10.0f;
	}

	void CameraController::onDestroy() {
	}

	void CameraController::onUpdate(float deltaTime) {
		auto& transform = getComponent<TransformComponent>().transform;
		float speed = 15.0f;

		if (Input::isKeyPressed(TUSK_KEY_A))
			transform[3][0] -= speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_D))
			transform[3][0] += speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_W))
			transform[3][1] += speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_S))
			transform[3][1] -= speed * deltaTime;
	}
}