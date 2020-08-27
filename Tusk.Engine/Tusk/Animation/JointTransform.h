#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

namespace Tusk {
	class JointTransform {
	public:
		JointTransform() = default;
		JointTransform(glm::vec3 position, glm::quat rotation);
		glm::mat4 getLocalTransform();

		static JointTransform* interpolate(JointTransform beginFrame, JointTransform endFramme, float progression);

	private:
		glm::vec3 _position;
		glm::quat _rotation;
	};
}