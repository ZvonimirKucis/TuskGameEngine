#pragma once

#include "Animation.h"
#include "Joint.h"
#include "KeyFrame.h"

namespace Tusk {
	class Animator {
	public:
		Animator();

		void playAnimation(const Ref<Animation>& animation);
		void update(float deltaTime);

	private:
		void increaseAnimationTime(float deltaTime);
		std::map<std::string, glm::mat4> calculateCurrentAnimationPose();
		void applyPoseToJoints(std::map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform);

		std::vector<KeyFrame> getPreviousAndNextFrames();
		float calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame);
		std::map<std::string, glm::mat4> interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression);

	private:
		Ref<Animation> _currentAnimation;
		float _animationTime = 0;
	};
}