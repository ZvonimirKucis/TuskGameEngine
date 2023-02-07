#pragma once

#include "Camera.h"

namespace Tusk {
	class SceneCamera : public Camera {
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void setViewportSize(uint32_t width, uint32_t height);
		void setFOV(float value);
		void setPerspectiveNear(float value);
		void setPerspectiveFar(float value);

	private:
		void recalculateProjection();
	private:
		float _fov = 45.0f;
		float _perspectiveNear = 1.0f, _perspectiveFar = 100.0f;
		float _aspectRatio = 0.0f;
	};
}
