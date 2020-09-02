#pragma once

#include <pugixml.hpp>
#include "VertexSkinData.h"

namespace Tusk {
	class SkinLoader {
	public:
		SkinLoader(const pugi::xml_node& controllersNode, uint32_t maxWeights);

		std::vector<std::string> extractJointNames();
		std::vector<Ref<VertexSkin>> extractSkinData();

	private:
		std::vector<std::string> loadJointsList();
		std::vector<float> loadWeights();
		std::vector<uint32_t> getEffectiveJointsCounts();
		std::vector<Ref<VertexSkin>> getSkinData(const std::vector<uint32_t>& counts, const std::vector<float>& weights);

	private:
		uint32_t _maxWeights;
		pugi::xml_node _skinningData;
	};
}