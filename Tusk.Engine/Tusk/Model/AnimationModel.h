#pragma once

#include "Tusk/Animation/Animation.h"
#include "Tusk/Animation/Animator.h"
#include "Tusk/Animation/Joint.h"
#include "Mesh.h"

#include <glm/glm.hpp>

namespace Tusk {
	class AnimationModel {
    public:
		AnimationModel(const std::string& path);
		~AnimationModel();

		void update(float deltaTime);
		void playAnimation(const Ref<Animation>& animation);
		void draw();

		std::vector<glm::mat4> getJoinTransforms();

	private:
		void addJointsToArray(const Ref<Joint>& headJoint, std::vector<glm::mat4>& jointMatrices);

	private:
		const uint32_t MAX_JOINTS = 3;
		std::vector<glm::mat4> _transforms;

		Ref<Joint> _rootJoint;
		uint32_t _jointCount;
		Ref<Animator> _animator;
		Ref<Mesh> _mesh;
	};
}