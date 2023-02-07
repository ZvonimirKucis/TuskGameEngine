#include "tuskpch.h"

#include "VertexSkinData.h"

namespace Tusk {

	void VertexSkin::addJointEffect(uint32_t jointID, float weight) {
		_data.push_back(VertexSkinData(jointID, weight));
	}

	void VertexSkin::limitJointNumber(uint32_t maxJoints) {
		std::sort(_data.begin(), _data.end(), std::greater<VertexSkinData>());

		if (_data.size() > maxJoints) {
			removeExcessJointID(maxJoints);
		}
		else if (_data.size() < maxJoints) {
			fillEmptyWeights(maxJoints);
		}

		normalizeWeights(maxJoints);
	}

	void VertexSkin::fillEmptyWeights(uint32_t maxJoints) {
		while (_data.size() < maxJoints) {
			_data.push_back(VertexSkinData(0, 0));
		}
	}

	void VertexSkin::removeExcessJointID(uint32_t maxJoints) {
		while (_data.size() > maxJoints) {
			_data.erase(_data.end() - 1);
		}
	}

	void VertexSkin::normalizeWeights(uint32_t maxJoints) {
		float total = 0;

		for (int i = 0; i < maxJoints; i++) {
			total += _data[i].weight;
		}

		for (int i = 0; i < maxJoints; i++) {
			_data[i].weight = std::min(_data[i].weight / total, 1.0f);
		}
	}
}