#pragma once

#include "Animation.h"
#include "Joint.h"
#include "KeyFrame.h"

namespace Tusk {
	class Animator {
	public:
		Animator(const Ref<Joint>& rootJoint);

		void playAnimation(const Ref<Animation>& animation);
		void update(float deltaTime);

	private:
		void increaseAnimationTime(float deltaTime);
		std::map<std::string, glm::mat4> calculateCurrentAnimationPose();
		void applyPoseToJoints(std::map<std::string, glm::mat4> currentPose, const Ref<Joint>& joint, const glm::mat4& parentTransform);

		std::vector<Ref<KeyFrame>> getPreviousAndNextFrames();
		float calculateProgression(const Ref<KeyFrame>& previousFrame, const Ref<KeyFrame>& nextFrame);
		std::map<std::string, glm::mat4> interpolatePoses(const Ref<KeyFrame>& previousFrame, const Ref<KeyFrame>& nextFrame, float progression);

	private:
		Ref<Joint> _rootJoint;
		Ref<Animation> _currentAnimation;
		float _animationTime = 0;
	};
}