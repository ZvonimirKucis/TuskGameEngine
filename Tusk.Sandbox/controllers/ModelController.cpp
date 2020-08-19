#include "ModelController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	void ModelController::onCreate() {
	}

	void ModelController::onDestroy() {
	}

	void ModelController::onUpdate(float deltaTime) {
		auto& transform = getComponent<Tusk::TransformComponent>().transform;
		auto rot = transform.getRotation();
		rot.y -= deltaTime * 90.0f;
		transform.setRotation(rot);
	}
}