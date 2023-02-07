#include "tuskpch.h"

#include "SkinLoader.h"
#include "Tusk/Model/Utils/Utils.h"

namespace Tusk {

	SkinLoader::SkinLoader(const pugi::xml_node& controllersNode, uint32_t maxWeights) {
		_skinningData = controllersNode.child("controller").child("skin");
		_maxWeights = maxWeights;
	}

	std::vector<std::string> SkinLoader::extractJointNames() {
		return loadJointsList();
	}

	std::vector<Ref<VertexSkin>> SkinLoader::extractSkinData() {
		std::vector<float> weights = loadWeights();
		std::vector<uint32_t> effectorJointCounts = getEffectiveJointsCounts();
		return getSkinData(effectorJointCounts, weights);
	}

	std::vector<std::string> SkinLoader::loadJointsList() {
		std::vector<std::string> joints;

		pugi::xml_node inputNode = _skinningData.child("vertex_weights");
		std::string jointDataID = inputNode.find_child_by_attribute("input", "semantic", "JOINT").attribute("source").as_string();
		jointDataID.erase(0, 1);
		
		pugi::xml_node jointsNode = _skinningData.find_child_by_attribute("source", "id", jointDataID.c_str()).child("Name_array");
		std::vector<std::string> names = Utils::split(jointsNode.child_value(), ' ');
		for (std::string name : names) {
			joints.push_back(name);
		}
		
		return joints;
	}

	std::vector<float> SkinLoader::loadWeights() {
		std::vector<float> weights;

		pugi::xml_node inputNode = _skinningData.child("vertex_weights");
		std::string weightsDataID = inputNode.find_child_by_attribute("input", "semantic", "WEIGHT").attribute("source").as_string();
		weightsDataID.erase(0, 1);

		pugi::xml_node weightsNode = _skinningData.find_child_by_attribute("source", "id", weightsDataID.c_str()).child("float_array");
		std::vector<std::string> rawWeights = Utils::split(weightsNode.child_value(), ' ');
		for (std::string weight : rawWeights) {
			weights.push_back(std::stof(weight));
		}

		return weights;
	}

	std::vector<uint32_t> SkinLoader::getEffectiveJointsCounts() {
		std::vector<uint32_t> counts;

		pugi::xml_node inputNode = _skinningData.child("vertex_weights");
		std::vector<std::string> rawData = Utils::split(inputNode.child("vcount").child_value(), ' ');
		for (std::string count : rawData) {
			counts.push_back(std::stoi(count));
		}

		return counts;
	}

	std::vector<Ref<VertexSkin>> SkinLoader::getSkinData(const std::vector<uint32_t>& counts, const std::vector<float>& weights) {
		std::vector<Ref<VertexSkin>> skinningData;

		pugi::xml_node inputNode = _skinningData.child("vertex_weights");
		pugi::xml_node dataNode = inputNode.child("v");
		std::vector<std::string> rawData = Utils::split(dataNode.child_value(), ' ');

		uint32_t pointer = 0;
		for (uint32_t count : counts) {
			Ref<VertexSkin> skinData = CreateRef<VertexSkin>();
			for (uint32_t i = 0; i < count; i++) {
				uint32_t jointId = std::stoi(rawData[pointer++]);
				uint32_t weightId = std::stoi(rawData[pointer++]);
				skinData->addJointEffect(jointId, weights[weightId]);
			}
			skinData->limitJointNumber(_maxWeights);
			skinningData.push_back(skinData);
		}
		return skinningData;
	}
}