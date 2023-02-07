#include "tuskpch.h"

#include "JointTransform.h"

namespace Tusk {
	JointTransform::JointTransform(glm::vec3 position, glm::quat rotation)
		:_position(position), _rotation(rotation){}

	glm::mat4 JointTransform::getLocalTransform() {
		return glm::translate(glm::mat4(1.0f), _position) * glm::mat4_cast(_rotation);
	}

	Ref<JointTransform> JointTransform::interpolate(const Ref<JointTransform>& beginFrame, const Ref<JointTransform>& endFrame, float progression) {
		glm::vec3 pos = beginFrame->_position * (1.0f - progression) + endFrame->_position * progression;
		glm::quat rot = glm::slerp(beginFrame->_rotation, endFrame->_rotation, progression);
		return  CreateRef<JointTransform>(pos, rot);
	}

}