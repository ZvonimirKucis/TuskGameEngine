#pragma once

#include "Tusk/Model/Mesh.h"
#include "Tusk/Animation/Animation.h"
#include "Tusk/Animation/Joint.h"

namespace Tusk {
	class ColladaLoader {
	public:
		static Ref<Mesh> loadModel(const std::string& path);
		static Ref<Mesh> loadAnimatedModel(const std::string& path, uint32_t maxJoints, Ref<Joint>& rootJoint, uint32_t* jointCount);
		static Ref<Animation> loadAnimation(const std::string& path);
	};
}