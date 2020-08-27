#include "tuskpch.h"

#include "Animator.h"

namespace Tusk {
	Animator::Animator() {

	}

	void Animator::playAnimation(const Ref<Animation>& animation) {
		_animationTime = 0;
		_currentAnimation = animation;
	}

	void Animator::update(float deltaTime) {
		if (!_currentAnimation)
			return;
		increaseAnimationTime(deltaTime);
		std::map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPose();
		//applyPoseToJoints(currentPose, , glm::mat4(1.0f));
	}

	void Animator::increaseAnimationTime(float deltaTime) {
		_animationTime += deltaTime;
		if (_animationTime > _currentAnimation->getLength())
			_animationTime = fmod(_animationTime, _currentAnimation->getLength());
	}

	std::map<std::string, glm::mat4> Animator::calculateCurrentAnimationPose() {
		std::vector<KeyFrame> frames = getPreviousAndNextFrames();
		float progression = calculateProgression(frames[0], frames[1]);
		return interpolatePoses(frames[0], frames[1], progression);
	}

	void Animator::applyPoseToJoints(std::map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform) {
		glm::mat4 currentLocalTransform = currentPose[joint.getName()];
		glm::mat4 currentTransform = parentTransform * currentLocalTransform;
		for (Joint childJoint : joint.getChildren()) {
			applyPoseToJoints(currentPose, childJoint, currentTransform);
		}
		currentTransform = currentTransform * joint.getInvertedBindTransform();
		joint.setAnimationTransform(currentTransform);
	}

	std::vector<KeyFrame> Animator::getPreviousAndNextFrames() {
		std::vector<KeyFrame> frames = _currentAnimation->getKeyFrames();
		KeyFrame previousFrame = frames[0];
		KeyFrame nextFrame = frames[0];

		for (int i = 1; i < frames.size(); i++) {
			nextFrame = frames[i];
			if (nextFrame.getTimeStamp() > _animationTime) {
				break;
			}
			previousFrame = frames[i];
		}

		return std::vector<KeyFrame> {previousFrame, nextFrame};
	}

	float  Animator::calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame) {
		float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
		float currentTime = _animationTime - previousFrame.getTimeStamp();
		return currentTime / totalTime;
	}

	std::map<std::string, glm::mat4> Animator::interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression) {
		std::map<std::string, glm::mat4> currentPose;
		for (std::pair<std::string, JointTransform> data : previousFrame.getJointKeyFrames()) {
			std::string jointName = data.first;
			JointTransform previousTransform = previousFrame.getJointKeyFrames()[jointName];
			JointTransform nextTransform = nextFrame.getJointKeyFrames()[jointName];
			JointTransform* currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
			currentPose.insert(std::pair<std::string, glm::mat4>(jointName, currentTransform->getLocalTransform()));
		}
		return currentPose;
	}
}