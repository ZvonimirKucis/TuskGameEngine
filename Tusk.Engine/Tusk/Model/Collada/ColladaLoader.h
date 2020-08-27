#pragma once

#include "../Mesh.h"

namespace Tusk {
	class ColladaLoader {
	public:
		static Ref<Mesh> loadModel(const std::string& path);
		static void loadAnimatedModel(const std::string& path);
		static void loadAnimation(const std::string& path);

	private:
		static std::string readStringFromFile(const std::string& path);
	};
}