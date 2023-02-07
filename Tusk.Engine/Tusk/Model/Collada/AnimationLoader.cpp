#include "tuskpch.h"

#include "AnimationLoader.h"
#include "Tusk/Model/Utils/Utils.h"

#include <glm/gtc/type_ptr.hpp>

namespace Tusk {
	AnimationLoader::AnimationLoader(pugi::xml_node animationData) 
		:_animationData(animationData){}

	Ref<Animation> AnimationLoader::extractAnimation() {
		std::string rootNode = "Torso";
		
		std::vector<float> times = getKeyTimes();
		float duration = times[times.size() - 1];

		std::vector<Ref<KeyFrame>> keyFrames = initKeyFrames(times);
		for (pugi::xml_node jointNode : _animationData.children("animation")) {
			loadKeyFrameTransforms(keyFrames, jointNode, rootNode);
		}

		return CreateRef<Animation>(duration, keyFrames);
	}

	std::vector<float> AnimationLoader::getKeyTimes() {
		std::vector<float> times;

		pugi::xml_node timeData = _animationData.child("animation").child("source").child("float_array");
		std::string str = timeData.child_value();
		
		std::replace(str.begin(), str.end(), '\n', ' ');
		str = Utils::trim(str);
		std::vector<std::string> rawTimes = Utils::split(str, ' ');

		for (uint32_t i = 0; i < rawTimes.size(); i++) {
			times.push_back(std::stof(rawTimes[i]));
		}

		return times;
	}

	std::vector<Ref<KeyFrame>> AnimationLoader::initKeyFrames(const std::vector<float>& times) {
		std::vector<Ref<KeyFrame>> keyFrames;

		for (uint32_t i = 0; i < times.size(); i++) {
			keyFrames.push_back(CreateRef<KeyFrame>(times[i]));
		}

		return keyFrames;
	}

	void AnimationLoader::loadKeyFrameTransforms(std::vector<Ref<KeyFrame>>& keyFrames, pugi::xml_node jointNode, std::string rootNode) {
		std::string jointNameID = getJointName(jointNode);
		//std::cout << jointNameID << std::endl;
		std::string dataID = getDataID(jointNode);

		pugi::xml_node transformData = jointNode.find_child_by_attribute("source", "id", dataID.c_str()).child("float_array");
		std::string str = transformData.child_value();
		
		std::replace(str.begin(), str.end(), '\n', ' ');
		str = Utils::trim(str);
		std::vector<std::string> rawData = Utils::split(str, ' ');

		bool isRoot = strcmp(jointNameID.c_str(), rootNode.c_str()) == 0;
		processTransforms(jointNameID, rawData, keyFrames, isRoot);
	}

	void AnimationLoader::processTransforms(std::string jointName, const std::vector<std::string>& rawData, std::vector<Ref<KeyFrame>>& keyFrames, bool isRoot) {
		float matrixData[16];

		for (uint32_t i = 0; i < keyFrames.size(); i++) {
			for (uint32_t j = 0; j < 16; j++) {
				matrixData[j] = std::stof(rawData[i* 16 + j]);
			}

			glm::mat4 transform = glm::make_mat4(matrixData);
			transform = glm::transpose(transform);
			if (isRoot)
				transform = Utils::correction * transform;
			keyFrames[i]->addJointTransform(jointName, convertTransformMatrixToJointTransform(transform));
		}
	}

	Ref<JointTransform> AnimationLoader::convertTransformMatrixToJointTransform(const glm::mat4& transform) {
		glm::quat rotation = Utils::quaternionFromMatrix(transform);
		glm::vec3 translation = glm::vec3(transform[3][0], transform[3][1], transform[3][2]);

		return CreateRef<JointTransform>(translation, rotation);
	}

	std::string AnimationLoader::getJointName(pugi::xml_node jointNode) {
		std::string data = jointNode.child("channel").attribute("target").as_string();
		return Utils::split(data, '/')[0];
	}

	std::string AnimationLoader::getDataID(pugi::xml_node jointNode) {
		std::string dataID = jointNode.child("sampler").find_child_by_attribute("input", "semantic", "OUTPUT").attribute("source").as_string();
		return dataID.erase(0, 1);
	}

	/*std::string AnimationLoader::findRootJointName() {
		pugi::xml_node skeleton = _jointHierarchy.child("visual_scene").find_child_by_attribute("node", "id", "Armature");
		return skeleton.child("node").attribute("id").as_string();
	}*/
}