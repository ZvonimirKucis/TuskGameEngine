#pragma once

#include "Mesh.h"
#include "Tusk/Animation/Joint.h"
#include "Tusk/Animation/Animation.h"

namespace Tusk {
	class Loader {
	public:
		static Ref<Mesh> loadModel(const std::string& path);
		static Ref<Mesh> loadAnimatedModel(const std::string& path, uint32_t maxJoints, Ref<Joint>& rootJoint, uint32_t* jointCount);
		static Ref<Animation> loadAnimation(const std::string& path);

	private:
		static std::string getFileExtension(const std::string& path);
	};
}