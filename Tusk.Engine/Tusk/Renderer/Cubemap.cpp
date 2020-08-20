#include "tuskpch.h"

#include "Cubemap.h"
#include "Tusk/Renderer/OpenGL/OpenGLCubemap.h"

namespace Tusk {

	Ref<Cubemap> Cubemap::create(const std::vector<std::string> faces) {
		return CreateRef<OpenGLCubemap>(faces);
	}

}