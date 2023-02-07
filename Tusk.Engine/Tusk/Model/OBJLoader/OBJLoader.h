#pragma once
#include "Tusk/Model/Mesh.h"

namespace Tusk {
	class OBJLoader {
	public:
		static Ref<Mesh> loadModel(const std::string& path);
	};
}