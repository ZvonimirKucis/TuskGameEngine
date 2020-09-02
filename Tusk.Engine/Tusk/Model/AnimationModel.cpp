#include "tuskpch.h"

#include "AnimationModel.h"
#include "Loader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Tusk {
	AnimationModel::AnimationModel(const std::string& path) {
		_mesh = Loader::loadAnimatedModel(path, MAX_JOINTS, _rootJoint, &_jointCount);
		_animator = CreateRef<Animator>(_rootJoint);
		_rootJoint->calculateInverseBindTransform(glm::mat4(1.0f));
		_transforms = std::vector<glm::mat4>(_jointCount);
	}

	void AnimationModel::update(float deltaTime) {
		_animator->update(deltaTime);
	}
	
	void AnimationModel::playAnimation(const Ref<Animation>& animation) {
		_animator->playAnimation(animation);
	}
	
	void AnimationModel::draw() {
		_mesh->draw();
	}

	std::vector<glm::mat4> AnimationModel::getJoinTransforms() {
		addJointsToArray(_rootJoint, _transforms);
		return _transforms;
	}

	void AnimationModel::addJointsToArray(const Ref<Joint>& headJoint, std::vector<glm::mat4>& jointMatrices) {
		jointMatrices[headJoint->getIndex()] = headJoint->getTransform();
		for (Ref<Joint> childJoint : headJoint->getChildren()) {
			addJointsToArray(childJoint, jointMatrices);
		}
	}

	AnimationModel::~AnimationModel() {
		_transforms.clear();
	}
}