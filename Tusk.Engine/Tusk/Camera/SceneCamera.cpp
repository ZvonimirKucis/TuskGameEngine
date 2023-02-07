#include "tuskpch.h"

#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	SceneCamera::SceneCamera() {
		recalculateProjection();
	}

	void SceneCamera::setFOV(float value) {
		_fov = value;
		recalculateProjection();
	}

	void SceneCamera::setPerspectiveNear(float value) {
		_perspectiveNear = value;
		recalculateProjection();
	}

	void SceneCamera::setPerspectiveFar(float value) {
		_perspectiveFar = value;
		recalculateProjection();
	}

	void SceneCamera::setViewportSize(uint32_t width, uint32_t height) {
		_aspectRatio = (float)width / (float)height;
		recalculateProjection();
	}

	void SceneCamera::recalculateProjection() {
		_projection = glm::perspective(glm::radians(_fov), _aspectRatio, _perspectiveNear, _perspectiveFar);
	}

}