#include "tuskpch.h"

#include "SkeletonLoader.h"
#include "Tusk/Model/Utils/Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Tusk {

	SkeletonLoader::SkeletonLoader(pugi::xml_node visualSceneNode, const std::vector<std::string>& boneOrder) {
		_armatureData = visualSceneNode.child("visual_scene").find_child_by_attribute("node", "id", "Armature");
		_boneOrder = boneOrder;
	}

	Ref<Joint> SkeletonLoader::extractBoneData() {
		pugi::xml_node headNode = _armatureData.child("node");
		return loadJointData(headNode, true);
	}

	Ref<Joint> SkeletonLoader::loadJointData(pugi::xml_node jointNode, bool isRoot) {
		Ref<Joint> joint = extractJointData(jointNode, isRoot);
		for (pugi::xml_node childNode : jointNode.children("node")) {
			joint->addChild(loadJointData(childNode, false));
		}
		return joint;
	}

	Ref<Joint> SkeletonLoader::extractJointData(pugi::xml_node jointNode, bool isRoot) {
		std::string nameID = jointNode.attribute("id").as_string();
		
		auto it = std::find(_boneOrder.begin(), _boneOrder.end(), nameID);
		uint32_t index = std::distance(_boneOrder.begin(), it);

		std::vector<std::string> matrixData = Utils::split(jointNode.child("matrix").child_value(), ' ');
		glm::mat4 matrix = glm::make_mat4(convertMatrixData(matrixData));

		matrix = glm::transpose(matrix);
		if (isRoot)
			matrix = Utils::correction * matrix;

		_jointCount++;
		return CreateRef<Joint>(index, nameID, matrix);
	}

	float* SkeletonLoader::convertMatrixData(std::vector<std::string> rawData) {
		float data[16];
		for (int i = 0; i < 16; i++) {
			data[i] = std::stof(rawData[i]);
		}
		return data;
	}

}