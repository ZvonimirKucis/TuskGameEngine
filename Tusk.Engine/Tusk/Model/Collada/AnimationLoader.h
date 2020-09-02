#pragma once

#include <pugixml.hpp>
#include "Tusk/Animation/Animation.h"
#include "Tusk/Animation/KeyFrame.h"
#include "Tusk/Animation/JointTransform.h"

namespace Tusk {
	class AnimationLoader {
	public:
		AnimationLoader(pugi::xml_node animationData, pugi::xml_node jointHierarchy);

		Ref<Animation> extractAnimation();

	private:
		std::string findRootJointName();
		std::vector<float> getKeyTimes();
		std::vector<Ref<KeyFrame>> initKeyFrames(const std::vector<float>& times);
		void loadKeyFrameTransforms(std::vector<Ref<KeyFrame>>& keyFrames, pugi::xml_node jointNode, std::string rootNode);
		std::string getJointName(pugi::xml_node jointNode);
		std::string getDataID(pugi::xml_node jointNode);
		void processTransforms(std::string jointName, const std::vector<std::string>& rawData, std::vector<Ref<KeyFrame>>& keyFrames, bool isRoot);
		Ref<JointTransform> convertTransformMatrixToJointTransform(const glm::mat4& transform);

	private:
		pugi::xml_node _animationData;
		pugi::xml_node _jointHierarchy;
	};
}