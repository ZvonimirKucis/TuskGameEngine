#include "tuskpch.h"

#include "Loader.h"
#include "Collada/ColladaLoader.h"
#include "OBJ/OBJLoader.h"

namespace Tusk {

	Ref<Mesh> Loader::loadModel(const std::string& path) {
		std::string extension = getFileExtension(path);
		
		if (std::strcmp(extension.c_str(), "dae") == 0) {
			return ColladaLoader::loadModel(path);
		} else if (std::strcmp(extension.c_str(), "obj") == 0) {
			return OBJLoader::loadModel(path);
		} else {
			Logger::Fatal("Model loader: file extension %s not supported, file: %s", extension.c_str(), path.c_str());
		}
	}

	Ref<Mesh> Loader::loadAnimatedModel(const std::string& path, uint32_t maxJoints, Ref<Joint>& rootJoint, uint32_t* jointCount) {
		std::string extension = getFileExtension(path);

		if (std::strcmp(extension.c_str(), "dae") == 0) {
			return ColladaLoader::loadAnimatedModel(path, maxJoints, rootJoint, jointCount);
		} else {
			Logger::Fatal("Animation loader: file extension %s not supported, file: %s", extension.c_str(), path.c_str());
		}
	}

	Ref<Animation> Loader::loadAnimation(const std::string& path) {
		std::string extension = getFileExtension(path);

		if (std::strcmp(extension.c_str(), "dae") == 0) {
			return ColladaLoader::loadAnimation(path);
		} else {
			Logger::Fatal("Animation loader: file extension %s not supported, file: %s", extension.c_str(), path.c_str());
		}
	}

	std::string Loader::getFileExtension(const std::string& path) {
		if (path.find_last_of(".") != std::string::npos)
			return path.substr(path.find_last_of(".") + 1);
		return "";
	}

}