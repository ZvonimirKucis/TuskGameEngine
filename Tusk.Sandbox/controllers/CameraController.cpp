#include "CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {
	float speed = 15.0f;

	void CameraController::onCreate() {
	}

	void CameraController::onDestroy() {
	}

	void CameraController::onUpdate(float deltaTime) {
		auto& transform = getComponent<TransformComponent>().transform;
		auto pos = transform.getPositon();
		
		if (Input::isKeyPressed(TUSK_KEY_A))
			pos.x -= speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_D))
			pos.x += speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_W))
			pos.y += speed * deltaTime;
		if (Input::isKeyPressed(TUSK_KEY_S))
			pos.y -= speed * deltaTime;

		transform.setPosition(pos);
	}
}