#pragma once

namespace Tusk {
	struct VertexSkinData {
		uint32_t jointID;
		float weight;

		VertexSkinData(uint32_t jointID, float weight) : jointID(jointID), weight(weight){}

		bool operator > (const VertexSkinData& vsd) const {
			return (weight > vsd.weight);
		}
	};

	class VertexSkin {
	public:
		void addJointEffect(uint32_t jointID, float weight);
		void limitJointNumber(uint32_t maxJoints);

		std::vector<VertexSkinData> getSkinData() { return _data; }

	private:
		void fillEmptyWeights(uint32_t maxJoints);
		void removeExcessJointID(uint32_t maxJoints);
		void normalizeWeights(uint32_t maxJoints);

	private:
		std::vector<VertexSkinData> _data;
	};
}