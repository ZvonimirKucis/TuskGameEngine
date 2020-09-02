#include "tuskpch.h"

#include "Animator.h"

namespace Tusk {
	Animator::Animator(const Ref<Joint>& rootJoint) 
		:_rootJoint(rootJoint){}

	void Animator::playAnimation(const Ref<Animation>& animation) {
		_animationTime = 0;
		_currentAnimation = animation;
	}

	void Animator::update(float deltaTime) {
		if (!_currentAnimation)
			return;
		increaseAnimationTime(deltaTime);
		std::map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPose();
		applyPoseToJoints(currentPose, _rootJoint, glm::mat4{ 1.0f });
	}

	void Animator::increaseAnimationTime(float deltaTime) {
		_animationTime += deltaTime;
		if (_animationTime > _currentAnimation->getLength())
			_animationTime = fmod(_animationTime, _currentAnimation->getLength());
	}

	std::map<std::string, glm::mat4> Animator::calculateCurrentAnimationPose() {
		std::vector<Ref<KeyFrame>> frames = getPreviousAndNextFrames();
		float progression = calculateProgression(frames[0], frames[1]);
		return interpolatePoses(frames[0], frames[1], progression);
	}

	void Animator::applyPoseToJoints(std::map<std::string, glm::mat4> currentPose,const Ref<Joint>& joint, const glm::mat4& parentTransform) {
		glm::mat4 currentLocalTransform = currentPose[joint->getName()];
		glm::mat4 currentTransform = parentTransform * currentLocalTransform;
		for (Ref<Joint> childJoint : joint->getChildren()) {
			applyPoseToJoints(currentPose, childJoint, currentTransform);
		}
		currentTransform = currentTransform * joint->getInvertedBindTransform();
		joint->setAnimationTransform(currentTransform);
	}

	std::vector<Ref<KeyFrame>> Animator::getPreviousAndNextFrames() {
		std::vector<Ref<KeyFrame>> frames = _currentAnimation->getKeyFrames();
		Ref<KeyFrame> previousFrame = frames[0];
		Ref<KeyFrame> nextFrame = frames[0];

		for (int i = 1; i < frames.size(); i++) {
			nextFrame = frames[i];
			if (nextFrame->getTimeStamp() > _animationTime) {
				break;
			}
			previousFrame = frames[i];
		}

		return std::vector<Ref<KeyFrame>> {previousFrame, nextFrame};
	}

	float  Animator::calculateProgression(const Ref<KeyFrame>& previousFrame, const Ref<KeyFrame>& nextFrame) {
		float totalTime = nextFrame->getTimeStamp() - previousFrame->getTimeStamp();
		float currentTime = _animationTime - previousFrame->getTimeStamp();
		return currentTime / totalTime;
	}

	std::map<std::string, glm::mat4> Animator::interpolatePoses(const Ref<KeyFrame>& previousFrame, const Ref<KeyFrame>& nextFrame, float progression) {
		std::map<std::string, glm::mat4> currentPose;
		for (std::pair<std::string, Ref<JointTransform>> data : previousFrame->getJointKeyFrames()) {
			std::string jointName = data.first;
			Ref<JointTransform> previousTransform = previousFrame->getJointKeyFrames()[jointName];
			Ref<JointTransform> nextTransform = nextFrame->getJointKeyFrames()[jointName];
			Ref<JointTransform> currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
			currentPose.insert(std::pair<std::string, glm::mat4>(jointName, currentTransform->getLocalTransform()));
		}
		return currentPose;
	}
}