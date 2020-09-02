#pragma once

#include <glm/glm.hpp>

namespace Tusk {

	class Joint {
	public:
		Joint(uint32_t index, std::string name, glm::mat4 localBindTransform);

		std::string getName() { return _name; }
		uint32_t getIndex() { return _index; }
		glm::mat4 getTransform() { return _transform; }
		glm::mat4 getInvertedBindTransform() { return _invertedBindTransform; }
		std::vector<Ref<Joint>> getChildren() { return _children; }

		void addChild(const Ref<Joint>& child);
		void setAnimationTransform(glm::mat4 transform);

		void calculateInverseBindTransform(glm::mat4 parentBindTransform);

	private:
		uint32_t _index;
		std::string _name;
		std::vector<Ref<Joint>> _children;

		glm::mat4 _transform;
		glm::mat4 _localBindTransform;
		glm::mat4 _invertedBindTransform;
	};
}