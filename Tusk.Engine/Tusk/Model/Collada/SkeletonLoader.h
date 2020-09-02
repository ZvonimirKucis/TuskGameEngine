#pragma once

#include <pugixml.hpp>

#include "Tusk/Animation/Joint.h"

namespace Tusk {
	class SkeletonLoader {
	public:
		SkeletonLoader(pugi::xml_node visualSceneNode, const std::vector<std::string>& boneOrder);

		uint32_t getJointCount() { return _jointCount; }
		Ref<Joint> extractBoneData();

	private:
		Ref<Joint> loadJointData(pugi::xml_node jointNode, bool isRoot);
		Ref<Joint> extractJointData(pugi::xml_node jointNode, bool isRoot);

		float* convertMatrixData(std::vector<std::string> rawData);

	private:
		pugi::xml_node _armatureData;
		std::vector<std::string> _boneOrder;
		uint32_t _jointCount = 0;
	};
}