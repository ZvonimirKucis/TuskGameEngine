#include "tuskpch.h"
#include <glm/glm.hpp>

#include "Joint.h"

namespace Tusk {

	Joint::Joint(uint32_t index, std::string name, glm::mat4 localBindTransform)
		: _index(index), _name(name), _localBindTransform(localBindTransform){}

	void Joint::addChild(const Ref<Joint>& child) {
		_children.push_back(child);
	}

	void Joint::setAnimationTransform(glm::mat4 transform) {
		_transform = transform;
	}

	void Joint::calculateInverseBindTransform(const glm::mat4& parentBindTransform) {
		glm::mat4 bindTransform = parentBindTransform * _localBindTransform;
		_invertedBindTransform = glm::inverse(bindTransform);
		for (Ref<Joint> child : _children)
			child->calculateInverseBindTransform(bindTransform);
	}
}