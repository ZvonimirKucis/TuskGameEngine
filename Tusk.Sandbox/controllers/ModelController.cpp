#include "ModelController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	void ModelController::onCreate() {
		auto& transform = getComponent<Tusk::TransformComponent>().transform;
		transform[3][2] = -10.0f;
	}

	void ModelController::onDestroy() {
	}

	void ModelController::onUpdate(float deltaTime) {
		auto& transform = getComponent<Tusk::TransformComponent>().transform;
		transform = glm::rotate(transform, deltaTime * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}