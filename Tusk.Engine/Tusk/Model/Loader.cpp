#include "tuskpch.h"

#include "Loader.h"
#include "Collada/ColladaLoader.h"

namespace Tusk {

	Ref<Mesh> Loader::loadModel(const std::string& path) {
		std::string extension = getFileExtension(path);
		
		if (std::strcmp(extension.c_str(), "dae") == 0)
			return ColladaLoader::loadModel(path);
	}

	std::string Loader::getFileExtension(const std::string& path) {
		if (path.find_last_of(".") != std::string::npos)
			return path.substr(path.find_last_of(".") + 1);
		return "";
	}

}