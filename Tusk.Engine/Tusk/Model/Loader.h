#pragma once

#include "Mesh.h"

namespace Tusk {
	class Loader {
	public:
		static Ref<Mesh> loadModel(const std::string& path);

	private:
		static std::string getFileExtension(const std::string& path);
	};
}